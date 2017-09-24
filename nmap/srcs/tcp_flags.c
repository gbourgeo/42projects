/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 06:31:30 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/15 06:31:35 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		get_tcp_flags(struct tcphdr *header, char *scan)
{
	if (!ft_strcmp(scan, "SYN")) {
		header->syn = 1;
	} else if (!ft_strcmp(scan, "FIN")) {
		header->fin = 1;
	} else if (!ft_strcmp(scan, "NULL")) {
		header->urg = 0;
		header->ack = 0;
		header->psh = 0;
		header->rst = 0;
		header->syn = 0;
		header->fin = 0;
	} else if (!ft_strcmp(scan, "XMAS")) {
		header->urg = 1;
		header->psh = 1;
		header->fin = 1;
	} else if (!ft_strcmp(scan, "ACK")) {
		header->ack = 1;
	}
}
