/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:18:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 07:18:24 by gbourgeo         ###   ########.fr       */
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
