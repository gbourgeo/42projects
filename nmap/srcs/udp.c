/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:43:32 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 03:17:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void			set_pseudogram(char *pseudogram, struct pseudo_header *psh, struct udphdr *header, int len, struct ip *ip_header, char *device)
{
	t_flag					*spoof = get_flag("spoof");

	psh->source_address = (spoof && spoof->value) ? inet_addr(spoof->value) : inet_addr(device);
	psh->dest_address = ip_header->ip_dst.s_addr;
	psh->placeholder = 0;
	psh->protocol = IPPROTO_UDP;
	psh->length = htons(sizeof(struct udphdr));
	ft_memset(pseudogram, 0, len);
	ft_memcpy(pseudogram, psh, sizeof(struct pseudo_header));
	ft_memcpy(pseudogram + sizeof(struct pseudo_header), header, sizeof(struct tcphdr));
}

static bool				set_udp_header(t_thread_handler *handler, int port, int id)
{
	struct ip				*ip_header = (struct ip*)((void*)handler->buffer_raw);
	struct udphdr			header;
	struct pseudo_header	psh;
	int						len = sizeof(struct pseudo_header) + sizeof(struct udphdr);
	BYTE					pseudogram[len];

	header.source	= htons(id);
	header.dest		= htons(port);
	header.len		= htons(sizeof(struct udphdr));
	header.check	= 0;

	set_pseudogram((char*)&pseudogram, &psh, &header, len, ip_header, handler->nmap->device);
	header.check = checksum((unsigned short*)&pseudogram, len);
	ft_memcpy(handler->buffer_raw + sizeof(struct ip), &header, sizeof(struct udphdr));
	return true;
}

static bool			build_raw(t_thread_handler *handler, int port, int raw_len, char *host, int id)
{
	ft_memset(handler->buffer_raw, 0, raw_len);
	return (set_ipv4_header(handler, raw_len, host, IPPROTO_UDP) &&
			set_udp_header(handler, port, id));
}

static void			wait_answer_queue(t_thread_handler *thread_handler, int port, char *scan, int id, char *host)
{
	t_queue		*queue = new_queue(port, IPPROTO_UDP, scan, id, host);

	if (queue) {
		add_queue(queue);
	} else {
		pthread_mutex_unlock(&globals->queue_lock);
	}
}

void				udp_handler(t_thread_handler *thread_handler, char *scan, char *host)
{
	int 		raw_len				= sizeof(struct ip) + sizeof(struct udphdr);
	int			ports_len			= thread_handler->ports_len;
	int			start_index			= thread_handler->start;
	int			id					= 0;

	thread_handler->fd = init_socket(IPPROTO_UDP);
	if (thread_handler->fd != SOCKET_ERROR) {
		thread_handler->buffer_raw = (BYTE*)malloc(raw_len);
		if (thread_handler->buffer_raw != NULL) {
			while (ports_len)
			{
				id = get_id();
				if (!build_raw(thread_handler, thread_handler->nmap->port[start_index], raw_len, host, id))
					break ;
				if ((send_socket_raw(thread_handler, raw_len, thread_handler->nmap->port[start_index])) > 0) {
					wait_answer_queue(thread_handler, thread_handler->nmap->port[start_index], scan, id, host);
				} else { pthread_mutex_unlock(&globals->queue_lock); }
				ports_len--;
				start_index++;
			}
			ft_strdel(&thread_handler->buffer_raw);
		}
		close(thread_handler->fd);
	}
}
