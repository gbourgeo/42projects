/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_home_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 22:56:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/14 19:29:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			k_home(t_env *e)
{
	if (e->pos != 0)
	{
		e->pos = 0;
		ft_tgoto(&e->origin);
		ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	}
}

void			k_end(t_env *e)
{
	ft_pos(ft_strlen(&e->hist->cmd[e->pos]), e);
}
