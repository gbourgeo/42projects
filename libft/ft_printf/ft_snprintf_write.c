/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:05:56 by root              #+#    #+#             */
/*   Updated: 2018/04/11 03:13:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_base_printf.h"

void		ft_snprintf_write(t_dt *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (data->str_size <= 1)
		return ;
	while (data->str[i])
		i++;
	while (j < data->pos && data->str_size > 1)
	{
		data->str[i + j] = data->buff[j];
		j++;
		data->str_size--;
	}
	data->str[i + j] = '\0';
	data->ret += j;
}
