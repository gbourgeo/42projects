/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 06:32:02 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/20 06:32:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*get_port_service(int port, u_char proto)
{
	char *proto_string = (proto == IPPROTO_TCP) ? "tcp" : "udp";
	struct servent *appl_name;

	appl_name = getservbyport(htons(port), proto_string);
	if (appl_name) {
		return ft_strdup(appl_name->s_name);
	} else {
		return (ft_strdup("Unassigned"));
	}
}
