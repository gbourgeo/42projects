/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_suppr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 17:32:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/13 18:14:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void		ft_key_suppr(t_env *e)
{
	e->pos--;
	ft_deletechar(e->history->command, e->pos);
	tputs(ft_tgetstr("le"), 1, ft_pchar);
	tputs(ft_tgetstr("dc"), 1, ft_pchar);
}

void		ft_key_del(t_env *e)
{
	e->pos--;
	ft_deletechar(e->history->command, e->pos);
	tputs(ft_tgetstr("dc"), 1, ft_pchar);
}
