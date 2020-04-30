/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:51:06 by frmarinh          #+#    #+#             */
/*   Updated: 2020/04/30 12:38:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "options.h"
#include "libft.h"
#include "ft_printf.h"

static void		print_start(t_params *e)
{
	gettimeofday(&e->start_time, NULL);
	ft_printf("\nStarting %s at %s\n",
		e->progname,
		get_time("%Y-%m-%d %H:%M %Z", &e->start_time));
}

static void 	print_info(t_params *e)
{
	ft_printf("\n-- Scan Configurations --\n");
	ft_printf("Target IP-Address     :");
	for (t_addr *ptr = e->addresses; ptr; ptr = ptr->next)
	{
		ft_printf(" %s", ptr->name);
	}
	ft_printf("\nNo of Ports to scan   : %d\n", e->ports_nb);
	ft_printf("Scan performed        : ");
	for (int i = 0; e->scans[i]; i++)
	{
		ft_printf("%s ", e->scans[i]);
	}
	ft_printf("\nNo of threads         : %d\n", e->threads_nb);
	ft_printf("No of retry           : %d\n", e->retry);
	ft_printf("Scan delay            : TCP %d\n\n", e->tcp_timeout);
}

static void		init_params(char *prog, t_params *e)
{
	char		errbuf[PCAP_ERRBUF_SIZE];

	ft_bzero(e, sizeof(*e));
	if ((e->progname = ft_strrchr(prog, '/')) == NULL)
		e->progname = prog;
	else
		e->progname++;
	if (!(e->ports = ft_memalloc(NM_MAX_PORTS_SCAN * sizeof(*e->ports))))
		nmap_error(e, "Ports allocation failed.");
	for (e->ports_nb = 0; e->ports_nb < NM_MAX_PORTS_SCAN; e->ports_nb++)
		e->ports[e->ports_nb] = e->ports_nb + 1;
	if (!(e->scans = ft_strsplit(SUPPORTED_SCANS, '/')))
		nmap_error(e, "Scans allocation failed.");
	e->scans_nb = ft_tablen(e->scans);
	e->threads_nb = 1;
	if (!(e->threads = ft_memalloc(sizeof(*e->threads) * e->threads_nb)))
		nmap_error(e, "Threads allocation failed.");
	for (unsigned int i = 0; i < e->threads_nb; i++)
	{
		if (!(e->threads[i] = ft_memalloc(sizeof(**e->threads))))
			nmap_error(e, "Thread %d allocation failed.", i);
	}
	e->retry = DEFAULT_RETRY_NB;
	e->tcp_timeout = DEFAULT_TCP_TIMEOUT;
	if (pcap_findalldevs(&e->interfaces, errbuf) != 0)
		nmap_error(e, "%s.", errbuf);
	pthread_mutex_init(&e->socket_lock, NULL);
}

static void		init_data(t_params *e)
{
	/* Total number of operations to be performed (scans per port per addresses). */
	e->total_operations = e->ports_nb * e->scans_nb;
	e->data = ft_memalloc(e->total_operations * sizeof(*e->data));
	if (e->data == NULL)
		nmap_error(e, "Global Data allocation failed.");
}

static void		assign_data(t_addr *addr, t_params *e)
{
	int			scan;
	int			port;
	int			id;

	scan = 0;
	port = 0;
	id = 59000;
	if (e->verbose || e->debug)
	{
		ft_printf("Initiating");
		for (int i = 0; e->scans[i]; i++)
				ft_printf(" %s", e->scans[i]);
		ft_printf(" Scan at %s\n", get_time("%H:%M", &e->start_time));
		if (e->addresses_nb > 1)
			ft_printf("Scanning %d hosts [%d ports/host]\n", e->addresses_nb, e->ports_nb);
		else
			ft_printf("Scanning %s (%s) [%d ports]\n", e->addresses->name, e->addresses->hostaddr, e->ports_nb);
	}
	for (unsigned int i = 0; i < e->total_operations; i++)
	{
		if (i && i % e->ports_nb == 0)
		{
			port = 0;
			++scan;
		}
		if (i && i % (e->scans_nb * e->ports_nb) == 0)
		{
			port = 0;
			scan = 0;
		}
		e->data[i].addr = addr;
		e->data[i].scan = e->scans[scan];
		e->data[i].port = e->ports[port];
		e->data[i].id = id++;
		if (!ft_strcmp(e->scans[scan], "SYN"))
			e->data[i].response.filtered = 1;
		++port;
	}
}

int				main(int argc, char **argv)
{
	t_params	e;

	(void)argc;
	ft_memset(&g_global, 0, sizeof(g_global));
	init_params(argv[0], &e);
	get_options(argv, &e);
	print_start(&e);
	print_info(&e);
	init_address_resolution(&e.addresses, e.debug);
	if (!e.addresses)
		ft_printf("WARNING: No targets were specified, so 0 hosts scanned.\n");
	else
	{
		init_data(&e);
		for (t_addr *addr = e.addresses; addr; addr = addr->next)
		{
			assign_data(addr, &e);
			init_pcap(addr, &e);
			init_threads(&e);
			launch_pcap(&e);
			scan_report(addr, &e);
		}
	}
	free_params(&e);
	return (0);
}
