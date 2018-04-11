/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 04:03:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 04:03:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

void		ft_sprintf_write(t_dt *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->str[i])
		i++;
	while (j < data->pos)
	{
		data->str[i + j] = data->buff[j];
		j++;
	}
	data->str[i + j] = '\0';
	data->ret += j;
}
