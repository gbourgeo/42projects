/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:09:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 23:38:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			quote_prompt(t_env *e)
{
	tputs(ft_tgetstr("cr"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	ft_putstr_fd((*e->quote == '\'') ? "quote> " : "dquote> ", e->fd);
	e->prpt = (*e->quote == '\'') ? 7 : 8;
	ft_bzero(e->buf, READ_SIZE);
	cursor_position(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
}

static char		*quotes_check(t_env *e)
{
	int			i;

	i = 0;
	e->quote = NULL;
	while (e->hist->cmd[i])
	{
		if (e->hist->cmd[i] == '\'' || e->hist->cmd[i] == '"')
		{
			if (e->quote == NULL)
				e->quote = &e->hist->cmd[i];
			else if (*e->quote == e->hist->cmd[i])
				e->quote = NULL;
		}
		i++;
	}
	return (e->quote);
}

int					quotes_command(t_env *e)
{
	size_t			pos;
	int				len;

	if (quotes_check(e) != NULL)
	{
		len = ft_strlen(e->buf);
		if (ft_strlen(e->hist->cmd) + len >= e->hist->cmd_size)
		{
			e->hist->cmd_size += CMD_SIZE;
			if (!(e->hist->cmd = ft_realloc(e->hist->cmd, e->hist->cmd_size)))
				ft_exit_all("Malloc failed.");
		}
		ft_insert_str(&e->hist->cmd[e->pos], e->buf, len);
		ft_pos(len, e);
		pos = ft_strlen(e->hist->cmd);
		quote_prompt(e);
		while  ((len = read(e->fd, e->buf, READ_SIZE)) > 0)
		{
			if (K_PRINT(e))
				read_command(len, e);
			else if (ENTER(e))
			{
				write(e->fd, "\n", 1);
				if (quotes_check(e) == NULL)
					break ;
				return (quotes_command(e));
			}
			else if (KEYPAD(e) || K_SUPPR(e))
				keypad_command(e);
			else if (COPY_KEY(e))
				copy_command(e);
			else if (CTRL_C(e))
				return (write(e->fd, "\n", 1));
			if (!SHFT_KEY(e) && !CT_SH_KEY(e) && e->cpy.cpy != 0)
				rewrite_command(&e->hist->cmd[pos], e);
			ft_bzero(e->buf, len);
		}
	}
	return (0);
}
