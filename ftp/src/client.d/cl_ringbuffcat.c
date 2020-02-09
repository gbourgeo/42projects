/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ringbuffcat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:41:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:21:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

char			*cl_ringbuffcat(char *buff, int size, t_buff *ring)
{
	int			i;
	char		*ptr;

	i = ft_strlen(buff);
	ptr = ring->head;
	while (ptr != ring->tail && i < size)
	{
		buff[i++] = *ptr++;
		if (ptr > ring->buff + sizeof(ring->buff))
			ptr = ring->buff;
	}
	buff[i] = '\0';
	return (buff);
}
