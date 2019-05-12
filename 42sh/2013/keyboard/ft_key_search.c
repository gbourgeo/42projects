/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 16:03:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/06 18:39:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_key_search(char *buf, t_env *e)
{
	if (K_UP && e->history->next)
	{
		ft_aff_history(e, 1);
		e->pos = ft_strlen(e->history->command);
	}
	else if (K_DOWN && e->history->prev)
	{
		ft_aff_history(e, 0);
		e->pos = ft_strlen(e->history->command);
	}
	else if (K_LEFT && e->pos > 0)
	{
		tputs(ft_tgetstr("le"), 1, ft_pchar);
		e->pos--;
	}
	else if (K_RIGHT && e->pos < (int)ft_strlen(e->history->command))
	{
		tputs(ft_tgetstr("nd"), 1, ft_pchar);
		e->pos++;
	}
}
