/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:44:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/15 04:02:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			check_cmd_len(t_env *e)
{
	e->hist->cmd_len = (e->cmd->save != NULL) ?
		ft_strlen(e->cmd->save) : e->cmd->cmd_len;
	if (e->hist->cmd_len >= e->hist->cmd_size)
	{
		while (e->hist->cmd_len >= e->hist->cmd_size)
			e->hist->cmd_size += CMD_SIZE;
		if (!(e->hist->cmd = ft_realloc(e->hist->cmd, e->hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
	else if (e->hist->cmd_len < e->hist->cmd_size - CMD_SIZE)
	{
		while (e->hist->cmd_len < e->hist->cmd_size - CMD_SIZE)
			e->hist->cmd_size -= CMD_SIZE;
		if (!(e->hist->cmd = ft_realloc(e->hist->cmd, e->hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
}

static void			aff_cmd(t_env *e)
{
	e->cpy.cpy = 0;
	e->pos = 0;
	check_cmd_len(e);
	if (e->cmd->save)
	{
		ft_strncpy(e->hist->cmd, e->cmd->save, e->hist->cmd_size);
		free(e->cmd->save);
		e->cmd->save = NULL;
	}
	else
		ft_strncpy(e->hist->cmd, e->cmd->cmd, e->hist->cmd_size);
	ft_tgoto(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	ft_putstr_fd(e->hist->cmd, e->fd);
	ft_pos(e->hist->cmd_len, e);
}

void				historic_command(t_env *e)
{
	if (K_UP(e))
	{
		if (e->cmd->next)
		{
			if (e->cmd->prev == NULL || ft_strcmp(e->hist->cmd, e->cmd->cmd))
				e->cmd->save = ft_strdup(e->hist->cmd);
			e->cmd = e->cmd->next;
			aff_cmd(e);
		}
	}
	else if (K_DOWN(e))
	{
		if (e->cmd->prev)
		{
			if (ft_strcmp(e->hist->cmd, e->cmd->cmd))
				e->cmd->save = ft_strdup(e->hist->cmd);
			e->cmd = e->cmd->prev;
			aff_cmd(e);
		}
	}
}
