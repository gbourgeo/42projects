/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:43:17 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 03:17:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void		set_pseudogram(char *pseudogram, struct pseudo_header *psh, struct tcphdr *header, int len, struct ip *ip_header, char *device)
{
	t_flag					*spoof = get_flag("spoof");

	psh->source_address = (spoof && spoof->value) ? inet_addr(spoof->value) : inet_addr(device);
	psh->dest_address = ip_header->ip_dst.s_addr;
	psh->placeholder = 0;
	psh->protocol = IPPROTO_TCP;
	psh->length = htons(sizeof(struct tcphdr));
	ft_memset(pseudogram, 0, len);
	ft_memcpy(pseudogram, psh, sizeof(struct pseudo_header));
	ft_memcpy(pseudogram + sizeof(struct pseudo_header), header, sizeof(struct tcphdr));
}

static bool					set_tcp_header(t_thread_handler *thread, int port, int raw_len, char *scan, int id)
{
	struct tcphdr			header;
	struct pseudo_header	psh;
	struct ip				*ip_header = (struct ip*)((void*)thread->buffer_raw);
	int						len = sizeof(struct pseudo_header) + sizeof(struct tcphdr);
	BYTE					pseudogram[len];

	header.source = htons(id);
	header.dest = htons(port); //16 bit in nbp format of destination port
	header.seq = htonl(1); //32 bit sequence number, initially set to zero
	header.ack_seq = 1; //32 bit ack sequence number, depends whether ACK is set or not
	header.doff = 5; //4 bits: 5 x 32-bit words on tcp header
	header.res1 = 0; //4 bits: Not used
	header.cwr = 0; //Congestion control mechanism
	header.ece = 0; //Congestion control mechanism
	header.urg = 0; //Urgent flag
	header.ack = 0; //Acknownledge
	header.psh = 0; //Push data immediately
	header.rst = 0; //RST flag
	header.syn = 0; //SYN flag
	header.fin = 0; //Terminates the connection
	header.window = htons(5840);//0xFFFF; //16 bit max number of databytes
	header.urg_ptr = 0; //16 bit indicate the urgent data. Only if URG flag is set
	header.check = 0; //16 bit check sum. Can't calculate at this point
	get_tcp_flags(&header, scan);
	set_pseudogram((char*)&pseudogram, &psh, &header, len, ip_header, thread->nmap->device);
	header.check = checksum((unsigned short *)pseudogram, len);
	ft_memcpy((void*)thread->buffer_raw + sizeof(struct ip), &header, sizeof(struct tcphdr));
	return true;
}

static void		wait_answer_queue(t_thread_handler *thread_handler, int port, char *scan, int id, char *host)
{
	t_queue		*queue = new_queue(port, IPPROTO_TCP, scan, id, host);

	if (queue) {
		add_queue(queue);
	} else {
		pthread_mutex_unlock(&globals->queue_lock);
	}
}

static bool		build_raw(t_thread_handler *thread_handler, int port, int raw_len, char *host, char *scan, int id)
{
	ft_memset(thread_handler->buffer_raw, 0, raw_len);
	return (set_ipv4_header(thread_handler, raw_len, host, IPPROTO_TCP) &&
			set_tcp_header(thread_handler, port, raw_len, scan, id));
}

void			tcp_handler(t_thread_handler *thread_handler, char *scan, char *host)
{
	int		raw_len 		= sizeof(struct ip) + sizeof(struct tcphdr);
	int		ports_len 		= thread_handler->ports_len;
	int		start_index 	= thread_handler->start;
	int		id				= 0;

	if ((thread_handler->fd = init_socket(IPPROTO_TCP)) != SOCKET_ERROR) {
		if ((thread_handler->buffer_raw = (BYTE*)malloc(raw_len))) {
			while (ports_len)
			{
				id = get_id();
				if (!build_raw(thread_handler, thread_handler->nmap->port[start_index], raw_len, host, scan, id))
					break ;
				if ((send_socket_raw(thread_handler, raw_len, thread_handler->nmap->port[start_index])) > 0) {
					wait_answer_queue(thread_handler, thread_handler->nmap->port[start_index], scan, id, host);
				} else { pthread_mutex_unlock(&globals->queue_lock); }
				ports_len--;
				start_index++;
			}
			ft_strdel(&thread_handler->buffer_raw);
		}
		close (thread_handler->fd);
	}
}
