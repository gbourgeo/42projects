/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_header.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:58:15 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 02:12:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

bool			set_ipv4_header(t_thread_handler *thread, int raw_len, char *host, u_char protocol)
{
	struct ip	header;
	t_flag		*spoof = get_flag("spoof");

	header.ip_src.s_addr = (spoof && spoof->value) ? inet_addr(spoof->value) : inet_addr(thread->nmap->device); // spoof flag
	if (!(inet_pton(AF_INET, host, &(header.ip_dst))))
	{
		printf("Can't set destination network address for %s\n", host);
		return false;
	}
	header.ip_ttl = DEFAULT_TTL; // Time to live
	header.ip_p = protocol; //  Protocol
	header.ip_v = 4; // IPv4
	header.ip_hl = sizeof(struct ip) >> 2; // IPv4 header length (4 bits)
	header.ip_tos = 0;
	header.ip_len = htons(raw_len);
	header.ip_off = 0;
	header.ip_id = htons(999);
	header.ip_sum = 0; // set checksum to zero to calculate
	header.ip_sum = checksum((unsigned short *) &header, sizeof(struct ip));
	ft_memcpy((void*)(thread->buffer_raw), &header, sizeof(struct ip));
	return true;
}
