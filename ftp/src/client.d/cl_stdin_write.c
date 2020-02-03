/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_stdin_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:56:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/03 17:31:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include "cl_main.h"

int			cl_stdin_write(t_buff *ring)
{
	int		ret;

	if (ring->tail == ring->head && ring->len != 0)
		return (IS_OK);
	if (ring->head < ring->tail)
		ret = write(STDOUT_FILENO, ring->head, ring->tail - ring->head);
	else
		ret = write(STDOUT_FILENO, ring->head,
		ring->buff + sizeof(ring->buff) - ring->head);
	if (ret < 0)
		return (ERR_WRITE);
	if ((ring->head += ret) >= ring->buff + sizeof(ring->buff))
		ring->head = ring->buff;
	ring->len = (ring->head > ring->tail) ? ring->head - ring->tail
	: ring->buff + sizeof(ring->buff) - ring->tail;
	return (IS_OK);
}
