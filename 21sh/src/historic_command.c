/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:44:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/02 22:02:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_hist			*hist_new(t_hist *next, size_t size)
{
	t_hist		*new;

	new = (t_hist *)malloc(sizeof(*new));
	if (new == NULL)
		ft_exit_all("Malloc failed.");
	new->prev = NULL;
	new->cmd = ft_strnew(size);
	if (new->cmd == NULL)
		ft_exit_all("Malloc failed.");
	new->cmd_size = CMD_SIZE;
	new->save = NULL;
	new->next = next;
	return (new);
}

t_hist			*hist_add(t_hist *new)
{
	if (new->prev && new->save && ft_strcmp(new->cmd, new->save))
	{
		while (e.hist->prev)
			e.hist = e.hist->prev;
		if (e.hist->cmd_size != new->cmd_size)
		{
			free(e.hist->cmd);
			if ((e.hist->cmd = ft_strnew(new->cmd_size)) == NULL)
				return (e.hist);
			e.hist->cmd_size = new->cmd_size;
		}
		ft_strncpy(e.hist->cmd, new->cmd, e.hist->cmd_size);
	}
	return (e.hist);
}

void			hist_clean(void)
{
	t_hist		*tmp;

	tmp = e.hist;
	while (tmp)
	{
		if (tmp->prev && tmp->save)
		{
			ft_strncpy(tmp->cmd, tmp->save, tmp->cmd_size);
			free(tmp->save);
		}
		tmp->save = NULL;
		tmp = tmp->next;
	}
}

static void		aff_cmd(void)
{
	char		*str;

	e.cpy.cpy = 0;
	ft_memcpy(&e.cursor, &e.origin, sizeof(e.cursor));
	e.pos = ft_strlen(e.hist->cmd);
	str = tgoto(ft_tgetstr("cm"), e.origin.x, e.origin.y);
	tputs(str, 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	write(e.fd, e.hist->cmd, e.pos);
	e.cursor.x += e.pos;
	while (e.cursor.x >= e.sz.ws_col)
	{
		if (e.cursor.y == e.sz.ws_row)
			e.origin.y--;
		else
			e.cursor.y++;
		e.cursor.x -= (e.sz.ws_col + 1);
	}
	if (e.hist->save == NULL)
		e.hist->save = ft_strdup(e.hist->cmd);
}

void			historic_command(void)
{
	if (K_UP && e.hist->next)
	{
		e.hist = e.hist->next;
		aff_cmd();
	}
	else if (K_DOWN && e.hist->prev)
	{
		e.hist = e.hist->prev;
		aff_cmd();
	}
}
