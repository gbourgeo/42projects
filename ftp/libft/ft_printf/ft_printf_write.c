/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 08:34:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 08:34:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_base_printf.h"

void		ft_printf_write(t_dt *data)
{
	data->ret += write(STDOUT_FILENO, data->buff, data->pos);
}
