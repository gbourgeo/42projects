/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:35:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/29 06:35:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void 				clear_clients(t_cl *cl, int size)
{
	for (int i = 0; i < size; i++) {
		cl[i].fd = -1;
		cl[i].try = 1;
		memset(cl[i].user, 0, sizeof(cl[i].user));
		memset(cl[i].rd, 0, sizeof(cl[i].rd));
		memset(cl[i].wr, 0, sizeof(cl[i].wr));
		cl[i].leaved = 0;
	}
}
