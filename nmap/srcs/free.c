/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 17:54:02 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 02:44:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void		free_hosts(t_host *host)
{
	if (host->next)
		free_hosts(host->next);
	if (host->addresses)
		ft_free_array((void **)host->addresses);
	if (host->address)
		ft_strdel(&host->address);
	free(host);
}

static void		free_scans(t_scan_type *scan)
{
	if (scan->next)
		free_scans(scan->next);
	if (scan->name)
		ft_strdel(&scan->name);
	free(scan);
}

static void		free_flags(t_flag *flags)
{
	if (!flags)
		return ;
	if (flags->next)
		free_flags(flags->next);
	if (flags->flag)
		ft_strdel(&flags->flag);
	if (flags->value)
		ft_strdel(&flags->value);
	free(flags);
}

static void		free_queues(t_queue *queue)
{
	if (!queue)
		return ;
	if (queue->next)
		free_queues(queue->next);
	if (queue->scan)
		ft_strdel(&queue->scan);
	if (queue->host)
		ft_strdel(&queue->host);
	if (queue->service)
		ft_strdel(&queue->service);
	free(queue);
}

void			free_datas(t_nmap *nmap)
{
	if (nmap)
	{
		if (nmap->hosts)
			free_hosts(nmap->hosts);
		if (nmap->scans)
			free_scans(nmap->scans);
		if (nmap->port)
			free(nmap->port);
		if (nmap->device)
			ft_strdel(&nmap->device);
		free(nmap);
	}
	free_flags(get_flags());
	free_queues(globals->all_queues);
}
