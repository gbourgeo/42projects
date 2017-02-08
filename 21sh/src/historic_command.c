/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:44:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/07 21:32:59 by gbourgeo         ###   ########.fr       */
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

t_hist			*hist_add(t_hist *new, t_env *e)
{
	if (new->prev)
	{
		while (e->hist->prev)
			e->hist = e->hist->prev;
		if (e->hist->cmd_size != new->cmd_size)
		{
			free(e->hist->cmd);
			if ((e->hist->cmd = ft_strnew(new->cmd_size)) == NULL)
				return (e->hist);
			e->hist->cmd_size = new->cmd_size;
		}
		ft_strncpy(e->hist->cmd, new->cmd, e->hist->cmd_size);
	}
	if (e->hist->next && !ft_strcmp(e->hist->cmd, e->hist->next->cmd))
		ft_bzero(e->hist->cmd, e->hist->cmd_size);
	return (e->hist);
}

void			hist_clean(t_hist *tmp, t_hist *next, size_t nb)
{
	while (tmp && nb < HIST_SIZE)
	{
		if (tmp->save)
		{
			ft_strncpy(tmp->cmd, tmp->save, tmp->cmd_size);
			free(tmp->save);
		}
		tmp->save = NULL;
		tmp = tmp->next;
		nb++;
	}
	while (tmp)
	{
		if (tmp->prev)
			tmp->prev->next = NULL;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->save)
			free(tmp->save);
		next = tmp->next;
		ft_memset(tmp, 0, sizeof(*tmp));
		free(tmp);
		tmp = next;
	}
}

static void		aff_cmd(t_env *e)
{
	char		*str;

	e->cpy.cpy = 0;
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	e->pos = ft_strlen(e->hist->cmd);
	str = tgoto(ft_tgetstr("cm"), e->origin.x, e->origin.y);
	tputs(str, 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	write(e->fd, e->hist->cmd, e->pos);
	e->cursor.x += e->pos;
	while (e->cursor.x >= e->sz.ws_col)
	{
		if (e->cursor.y == e->sz.ws_row)
			e->origin.y--;
		else
			e->cursor.y++;
		e->cursor.x -= (e->sz.ws_col + 1);
	}
	if (e->hist->prev && e->hist->save == NULL)
		e->hist->save = ft_strdup(e->hist->cmd);
}

void			historic_command(t_env *e)
{
	if (K_UP(e) && e->hist->next)
	{
		e->hist = e->hist->next;
		aff_cmd(e);
	}
	else if (K_DOWN(e) && e->hist->prev)
	{
		e->hist = e->hist->prev;
		aff_cmd(e);
	}
}
