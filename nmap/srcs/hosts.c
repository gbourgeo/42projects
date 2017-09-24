/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hosts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 16:08:20 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 01:26:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static t_host	*alloc_host(char *addr)
{
	t_host		*to_alloc;

	if (!(to_alloc = (t_host*)malloc(sizeof(struct s_host))))
		return NULL;
	to_alloc->address = addr;
	to_alloc->addresses = NULL;
	to_alloc->next = NULL;
	return (to_alloc);
}

static t_host	*add_host(t_host *head, char *addr)
{
	t_host		*tail = head;

	if (!head)
		return alloc_host(addr);
	while (tail->next)
		tail = tail->next;
	if ((tail->next = alloc_host(addr)) == NULL)
		printf("ft_nmap: Can't allocate memory for %s\n", addr);
	return head;
}

bool			load_hosts(bool multiple_host, t_nmap *nmap)
{
	t_flag		*flag	= NULL;
	int			fd		= 0;
	char		*hosts	= NULL;

	if (!multiple_host) {
		flag = get_flag("host");
		nmap->hosts = alloc_host(ft_strdup(flag->value));
	} else {
		flag = get_flag("file");
		if ((fd = open(flag->value, O_RDONLY)) == -1) {
			perror("ft_nmap");
			return false;
		}
		while (get_next_line(fd, &hosts) > 0) {
			nmap->hosts = add_host(nmap->hosts, hosts);
		}
		close(fd);
	}
	return nmap->hosts != NULL;
}
