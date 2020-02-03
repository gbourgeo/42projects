/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:02:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/03 23:16:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int		cl_client_write(const char *buf, t_buff *ring, t_client *cl)
{
	int			i;
	int			errnb;

	i = 0;
	if (buf)
		while (buf[i])
		{
			if (ring->len > 0)
			{
				*ring->tail++ = buf[i++];
				ring->len--;
			}
			else if ((errnb = cl_ncurses_write(ring, cl)) != IS_OK)
				return (errnb);
		}
	return (IS_OK);
}
