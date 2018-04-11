/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:42:31 by root              #+#    #+#             */
/*   Updated: 2018/04/11 01:40:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_base_printf.h"

void		ft_printf_write(t_dt *data)
{
	data->ret += write(STDOUT_FILENO, data->buff, data->pos);
}
