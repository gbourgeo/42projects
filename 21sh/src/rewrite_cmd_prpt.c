/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_cmd_prpt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 04:15:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 23:40:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "cm"		Position the cursor at line l, column c.
** "cr"		Move the cursor to the beginning of the line it is on.
** "cd"		Clear the line the cursor is on, and all the lines below it.
*/

void			rewrite_prompt(t_env *e)
{
	char		*str;

	str = tgoto(ft_tgetstr("cm"), e->origin.x, e->origin.y);
	tputs(str, 1, ft_pchar);
	tputs(ft_tgetstr("cr"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	prompt(e->env);
}

void			rewrite_command(char *cmd, t_env *e)
{
	int			i;
	char		*str;

	i = ft_strlen(e->hist->cmd);
	if (i)
	{
		str = tgoto(ft_tgetstr("cm"), e->origin.x, e->origin.y);
		tputs(str, 1, ft_pchar);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		ft_putstr_fd(cmd, e->fd);
		str = tgoto(ft_tgetstr("cm"), e->cursor.x, e->cursor.y);
		tputs(str, 1, ft_pchar);
	}
	e->cpy.cpy = 0;
}
