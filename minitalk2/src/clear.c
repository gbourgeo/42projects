/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:35:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/30 02:58:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void 				clear_clients(t_cl *cl, int size)
{
	for (int i = 0; i < size; i++) {
		cl[i].fd = -1;
		cl[i].try = 1;
		memset(cl[i].user, 0, sizeof(cl[i].user));
		memset(cl[i].rd, 0, BUF_CLIENTS);
		memset(cl[i].wr, 0, BUF_CLIENTS);
		cl[i].leaved = 0;
	}
}
