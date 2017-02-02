/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:39:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/02 19:20:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			treat_command(void)
{
	char		**args;

	rewrite_command();
	write(e.fd, "\n", 1);
	e.pos = 0;
	if (*e.hist->cmd)
	{
		args = ft_split_whitespaces(e.hist->cmd);
		if (args == NULL)
			ft_exit_all("Parsing failed.");
		restore_term();
		check_and_exec(args, e.env);
		redefine_term();
		e.hist = hist_add(e.hist);
		hist_clean();
		e.hist = hist_new(e.hist, CMD_SIZE);
		if (e.hist->next)
			e.hist->next->prev = e.hist;
	}
	if (e.hist->next)
		ft_putendl(e.hist->next->cmd);
	prompt(e.env);
	cursor_position(&e.origin);
	ft_memcpy(&e.cursor, &e.origin, sizeof(e.cursor));
}
