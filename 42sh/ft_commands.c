/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 05:40:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 18:34:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		read_command(char *buf, t_env *e)
{
	if (PRINTABLE_KEYS)
		ft_normal_keys(buf, e);
	else if (ENTER)
		treat_command(e);
	else if (KEYPAD)
		ft_key_search(buf, e);
	else if (SUPPR && e->pos > 0)
		ft_key_suppr(e);
	else if (CTRL_C)
		ft_control_c(e);
	else if (CTRL_D && !*e->history->command)
		ft_control_d(e);
	else if (DELETE && e->pos < (int)ft_strlen(e->history->command))
		ft_key_del(e);
}

void		treat_command(t_env *e)
{
	ft_putchar('\n');
	e->pos = 0;
	if (e->history->command && *e->history->command)
	{
		ft_term_restore(e);
		ft_parser(e);
		e->history = ft_add_to_hist(e->history);
		ft_define_new_term_cap(e);
	}
	prompt(e->env);
}
