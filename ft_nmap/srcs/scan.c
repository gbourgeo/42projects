/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 21:31:08 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 18:29:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static char			**get_host_addresses(struct hostent *host)
{
	char			**hosts		= NULL;
	struct in_addr	IP;
	int				i			= 0;
	int				len			= ft_array_len(host->h_addr_list) + 1;

	if (!(hosts = (char**)malloc(len * sizeof(char*))))
		return (NULL);
	i = 0;
	while (host->h_addr_list[i]) {
		IP.s_addr = *((uint32_t*) host->h_addr_list[i]);
		hosts[i++] = ft_strdup(inet_ntoa(IP));
	}
	hosts[i] = NULL;
	return (hosts);
}

static void			handler(t_thread_handler *thread_handler, char *scan, char *host)
{
	if (!ft_strcmp(scan, "UDP")) {
		udp_handler(thread_handler, scan, host);
	} else {
		tcp_handler(thread_handler, scan, host);
	}
}

static void			initialize_scan(t_thread_handler *thread_handler, char *scan_name)
{
	t_flag			*flag		= NULL;
	t_host			*hosts		= thread_handler->nmap->hosts;
	struct hostent	*host		= NULL;
	int				i			= 0;

	while (hosts) {
		if ((host = gethostbyname(hosts->address)) != NULL) {

			if (!hosts->addresses) {
				hosts->addresses = get_host_addresses(host);
			}
			if (hosts->addresses) {
				if ((flag = get_flag("deep")) != NULL) {
					while (hosts->addresses[i]) {
						handler(thread_handler, scan_name, hosts->addresses[i++]);
					}
				} else if (hosts->addresses[0]) {
					handler(thread_handler, scan_name, hosts->addresses[0]);
				}
			}
		} else {
			printf("Failed to resolve \"%s\".\n", hosts->address);
		}
		i = 0;
		hosts = hosts->next;
	}
}

void				start_scans(t_thread_handler *thread_handler)
{
	t_scan_type		*scans = thread_handler->nmap->scans;

	while (scans) {
		initialize_scan(thread_handler, scans->name);
		scans = scans->next;
	}
}
