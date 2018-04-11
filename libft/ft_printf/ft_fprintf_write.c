/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:59:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 04:00:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void		ft_fprintf_write(t_dt *data)
{
	void	*buf;

	buf = data->buff;
	data->ret += fwrite(buf, sizeof(*data->buff), data->pos, data->stream);
}
