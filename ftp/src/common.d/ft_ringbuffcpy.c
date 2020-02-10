/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ringbuffcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:50:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 18:37:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

char			*ft_ringbuffcpy(char *buff, int size, t_buff *ring)
{
	int			i;

	i = 0;
	while (ring->head != ring->tail && i < size)
	{
		buff[i++] = *ring->head++;
		if (ring->head >= ring->buff + CMD_BUFF_SIZE)
			ring->head = ring->buff;
	}
	buff[i] = '\0';
	return (buff);
}
