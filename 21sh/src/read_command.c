/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 03:37:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 03:58:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "cd"		Clear screen from the cursor position adn all the lines below.
*/

void			check_cmd(char buf, t_env *e)
{
	if ((buf == '\'' || buf == '"'))
	{
		if (e->quote == 0)
			e->quote = buf;
		else if (e->quote == buf)
			e->quote = 0;
	}
	ft_insert_str(&e->hist->cmd[e->pos], &buf, 1);
	e->hist->cmd_len++;
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	write(e->fd, &e->hist->cmd[e->pos], 1);
	ft_pos(1, e);
	if (e->hist->cmd[e->pos])
		rewrite_command(e);
}

void			check_cmd_len(int len, t_env *e)
{
	if (e->hist->cmd_len + len >= e->hist->cmd_size)
	{
		while (e->hist->cmd_len + len >= e->hist->cmd_size)
			e->hist->cmd_size += CMD_SIZE;
		if (!(e->hist->cmd = ft_realloc(e->hist->cmd, e->hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
	else if (e->hist->cmd_len + len < e->hist->cmd_size - CMD_SIZE)
	{
		while (e->hist->cmd_len + len < e->hist->cmd_size - CMD_SIZE)
			e->hist->cmd_size -= CMD_SIZE;
		if (!(e->hist->cmd = ft_realloc(e->hist->cmd, e->hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
}

void			read_command(int len, char *buf, t_env *e)
{
	int			i;

	i = 0;
	check_cmd_len(len, e);
	while (i < len)
	{
		if (buf[i] == ENTER)
			treat_command(e);
		else if (buf[i] == TAB)
			tab_command(e);
		else if (e->buf[i] > 31 && e->buf[i] < 127)
			check_cmd(buf[i], e);
		i++;
	}
}
