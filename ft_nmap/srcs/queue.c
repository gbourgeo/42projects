/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 02:48:21 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 02:32:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_queue			*new_queue(int port, u_char proto, char *scan, int id, char *host)
{
	t_queue		*new_queue = NULL;

	if (!(new_queue = (t_queue*)malloc(sizeof(struct s_queue))))
		return (NULL);
	new_queue->next = NULL;
	new_queue->port = port;
	new_queue->proto = proto;
	new_queue->scan = ft_strdup(scan);
	new_queue->done = false;
	new_queue->id = id;
	new_queue->filtered = true;
	new_queue->open = false;
	new_queue->host = ft_strdup(host);
	new_queue->service = get_port_service(port, proto);
	return (new_queue);
}

void			add_queue(t_queue *new_queue)
{
	if (globals->all_queues) {
		t_queue	*tmp = globals->all_queues;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_queue;
	} else {
		globals->all_queues = new_queue;
	}
	pthread_mutex_unlock(&globals->queue_lock);
}

t_queue			*find_queue(u_char proto, int id)
{
	pthread_mutex_lock(&globals->queue_lock);
	t_queue	*tmp = globals->all_queues;
	while (tmp)
	{
		if (id == -1 && tmp->proto == IPPROTO_UDP) {
			pthread_mutex_unlock(&globals->queue_lock);
			return (tmp);
		}
		if (tmp->id == id && tmp->proto == proto && !tmp->done) {
			pthread_mutex_unlock(&globals->queue_lock);
			return (tmp);
		}
		tmp = tmp->next;
	}
	pthread_mutex_unlock(&globals->queue_lock);
	return (NULL);
}
