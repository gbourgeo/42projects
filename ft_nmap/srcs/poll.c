/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 03:07:24 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/18 03:07:25 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void						start_poll_thread(t_thread_handler *threads)
{
	pthread_t	thread;
	pthread_create(&thread, NULL, poll_handler, threads);
	pthread_join(thread, NULL);
}

static int					get_len_threads(t_thread_handler *threads)
{
	int i = 0;
	while (threads)
	{
		i++;
		threads = threads->next;
	}
	return (i);
}

char						*guess_scan_type(struct tcphdr *header)
{
	if (header->syn && header->ack || header->rst && header->ack)
		return ("SYN");
	else if (header->rst)
		return ("ACK");
	return (NULL);
}

void						parse_tcp(int len, char *buf)
{
	struct tcphdr			*tcp_header = (struct tcphdr*)((void*)buf + sizeof(struct ip));
	char					*scan = guess_scan_type(tcp_header);
	t_queue					*queue = NULL;

	if (scan)
	{
		queue = find_queue(ntohs(tcp_header->dest), IPPROTO_TCP, scan);
		if (queue) {
			printf("%s, len: %d, source: %d\n", scan, len, ntohs(tcp_header->source));
			queue->done = true;
		}
	}
	/*if (queue) {
		printf("Queue found for port %d and scan type %s\n", queue->port, queue->scan);
	}*/
}

void						parse_message(int len, char *buf)
{
	struct ip				*ip_header = (struct ip*)((void*)buf);
	if (ip_header->ip_p == IPPROTO_TCP)
	{
		parse_tcp(len, buf);
	} else if (ip_header->ip_p == IPPROTO_UDP) {
		//parse_udp(len, buf);
	}
}

void						*poll_handler(void *handler)
{
	t_thread_handler		*threads = (t_thread_handler*)handler;
	int						nb_threads = get_len_threads(threads);
	char					buf[4096];
	struct pollfd			pfds[nb_threads];
	int n = 0;
	int i = 0;
	short revents;

	t_thread_handler *tmp = threads;
	while (tmp)
	{
		pfds[i].fd = tmp->fd;
		pfds[i].events = POLLIN;
		i++;
		tmp = tmp->next;
	}

	while (true) {
		if ((poll(pfds, nb_threads, -1)) != -1) {
			i = 0;
			while (i < nb_threads) {
				revents = pfds[i].revents;
	            if (revents & POLLIN) {
					n = read(pfds[i].fd, buf, sizeof(buf));
					if (n > 0) {
						parse_message(n, buf);
						//t_thread_handler	*current = get_thread_from_fd(threads, pfds[i].fd);
						//if (current) {
                			//printf("POLLIN i=%d n=%d buf=%.*s\n", i, n, n, buf);
						//}
					}
				}
				i++;
			}
		}
	}
	return (NULL);
}
