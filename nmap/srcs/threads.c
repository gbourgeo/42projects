/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 18:27:05 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/25 21:07:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void					free_threads(t_thread_handler *thread)
{
	if (!thread)
		return ;
	if (thread->next)
		free_threads(thread->next);
	free(thread);
}

static void					*in_thread(void *handler)
{
	t_thread_handler		*thread_handler = (t_thread_handler*)handler;

	if (thread_handler) {
		start_scans(thread_handler);
	}
	pthread_exit(NULL);
}

static t_thread_handler		*alloc_handler(t_nmap *nmap, int index, int len)
{
	t_thread_handler		*new = NULL;

	if (!(new = (t_thread_handler*)malloc(sizeof(struct s_thread_handler))))
		return (NULL);
	new->nmap = nmap;
	new->start = index;
	new->ports_len = len;
	new->fd = 0;
	new->next = NULL;
	return (new);
}

t_thread_handler			*new_thread(t_nmap *nmap, int index, int len)
{
	if (len > 0) {
		t_thread_handler	*handler = alloc_handler(nmap, index, len);
		if (handler) {
			pthread_create(&handler->thread, NULL, in_thread, handler);
			return (handler);
		}
	}
	return (NULL);
}

void						instantiate_threads(t_nmap *nmap)
{
	t_thread_handler		*threads = NULL;
	int i = 0, end_diff = 0, total = 0;
	int ports = nmap->ports_index / nmap->threads;

	while (i < nmap->threads)
	{
		int ports_plus = (i < nmap->threads - nmap->ports_index % nmap->threads) ? 0 : 1;
		threads = add_thread_handler(threads, new_thread(nmap, total, ports + ports_plus));
		total += ports + ports_plus;
		i++;
	}
	init_display(nmap);
	init_pcap(NULL, threads);
	while (true);
}
