/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:39:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 23:40:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			treat_command(t_env *e)
{
	char		*cmd;
	char		**args;

	rewrite_command(e->hist->cmd,e);
	write(e->fd, "\n", 1);
	if (*e->hist->cmd)
	{
		if ((e->ret = quotes_command(e)) == 0)
		{
			cmd = expansions_check(e);
			args = split_command(cmd);
			if (cmd)
				free(cmd);
			if (args == NULL)
				return (ft_putendl_fd("Parsing failed.", 2));
			restore_term();
			check_and_exec(args, &e->env);
			redefine_term();
		}
		e->hist = hist_add(e->hist, e);
		hist_clean(e->hist, NULL, 0);
		if (*e->hist->cmd)
			e->hist = hist_new(e->hist, CMD_SIZE);
		if (e->hist->next)
			e->hist->next->prev = e->hist;
	}
	e->pos = 0;
	prompt(e->env);
	cursor_position(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
}
