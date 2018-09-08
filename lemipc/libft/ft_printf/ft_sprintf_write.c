/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:59:42 by root              #+#    #+#             */
/*   Updated: 2018/04/11 03:13:54 by root             ###   ########.fr       */
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
