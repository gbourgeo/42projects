/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:44:30 by root              #+#    #+#             */
/*   Updated: 2018/04/11 02:25:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void		ft_fprintf_write(t_dt *data)
{
	void	*buf = data->buff;

	data->ret += fwrite(buf, sizeof(*data->buff), data->pos, data->stream);
}
