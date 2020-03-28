/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:51:06 by frmarinh          #+#    #+#             */
/*   Updated: 2020/03/28 16:29:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "options.h"
#include "libft.h"
#include "ft_printf.h"

static void		print_start(t_params *e)
{
	char		tbuf[128];
	struct tm	*local_time;

	time(&e->start);
	local_time = localtime(&e->start);
	strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M %Z", local_time);
	ft_printf("\nStarting %s at %s\n", e->progname, tbuf);
}

static void 	print_info(t_params *e)
{
	ft_printf("\n-- Scan Configurations --\n");
	ft_printf("Target IP-Address     : ");
	for (t_addr *ptr = e->addresses; ptr; ptr = ptr->next)
	{
		if (ptr != e->addresses)
			ft_printf("\t\t\t");
		ft_printf("%s (%s)\n", ptr->name, ptr->hostaddr);
	}
	ft_printf("No of Ports to scan   : %d\n", e->ports_nb);
	ft_printf("Scan performed        : ");
	for (int i = 0; e->scans[i]; i++)
	{
		ft_printf("%s ", e->scans[i]);
	}
	ft_printf("\nNo of threads         : %d\n\n", e->threads_nb);
}

static void		init_params(char *prog, t_params *e)
{
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
	for (int i = 0; i < e->threads_nb; i++)
	{
		if (!(e->threads[i] = ft_memalloc(sizeof(**e->threads))))
			nmap_error(e, "Thread %d allocation failed.", i);
	}
	e->pcap_timeout = DEFAULT_PCAP_TIMEOUT;
}

static void		init_global(t_params *e)
{
	int 		total;
	t_addr		*addr;
	int			scan;
	int			port;

	/* Total number of operations to be performed (scans per port per addresses). */
	total = e->addresses_nb * e->ports_nb * e->scans_nb;
	pthread_mutex_init(&g_global.id_lock, NULL);
	g_global.recv_timeout = e->pcap_timeout;
	g_global.device = e->device;
	g_global.data = ft_memalloc(total * sizeof(*g_global.data));
	if (g_global.data == NULL)
		nmap_error(e, "Global Data allocation failed.");
	addr = e->addresses;
	scan = 0;
	port = 0;
	for (int i = 0; i < total; i++)
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
			addr = addr->next;
		}
		g_global.data[i].addr = addr;
		g_global.data[i].scan = e->scans[scan];
		g_global.data[i].port = e->ports[port];
		++port;
	}
}

int				main(int argc, char **argv)
{
	t_params	e;

	(void)argc;
	init_params(argv[0], &e);
	print_start(&e);
	get_options(argv, &e);
	get_interface(&e);
	if (!e.addresses)
		ft_printf("WARNING: No targets were specified, so 0 hosts scanned.\n");
	else
	{
		print_info(&e);
		init_pcap(&e);
		init_global(&e);
		init_threads(&e);
	}
	free_params(&e);
	return (0);
}
