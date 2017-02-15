/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_cmd_prpt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 04:15:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/14 19:29:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "cm"		Position the cursor at line l, column c.
** "cr"		Move the cursor to the beginning of the line it is on.
** "cd"		Clear the line the cursor is on, and all the lines below it.
*/

void			rewrite_command(t_env *e)
{
	ft_tgoto(&e->origin);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	ft_putstr_fd(&e->hist->cmd[e->q_pos], e->fd);
	ft_tgoto(&e->cursor);
	e->cpy.cpy = 0;
}
