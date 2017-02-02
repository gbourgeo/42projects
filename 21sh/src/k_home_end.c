/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_home_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 22:56:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/02 23:02:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			k_home(void)
{
	char		*str;

	if (e.pos != 0)
	{
		e.pos = 0;
		ft_memcpy(&e.cursor, &e.origin, sizeof(e.cursor));
		str = tgoto(ft_tgetstr("cm"), e.origin.x, e.origin.y);
		tputs(str, 1, ft_pchar);
	}
}

void			k_end(void)
{
	ft_pos(ft_strlen(&e.hist->cmd[e.pos]));
}
