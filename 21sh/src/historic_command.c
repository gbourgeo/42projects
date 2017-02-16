/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:44:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/16 18:30:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			aff_cmd(t_env *e)
{
	size_t			len;
	char			*str;

	len = (e->cmd->save) ? ft_strlen(e->cmd->save) : e->cmd->cmd_len;
	str = (e->cmd->save) ? e->cmd->save : e->cmd->cmd;
	e->cpy.cpy = 0;
	e->pos = e->q_pos;
	e->hist->cmd_len = e->q_pos;
	check_cmd_len(len, e);
	ft_tgoto(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	ft_strclr(&e->hist->cmd[e->q_pos]);
	len = 0;
	while (str[len++])
		check_cmd(str[len - 1], e);
	if (e->cmd->save)
	{
		free(e->cmd->save);
		e->cmd->save = NULL;
	}
}

void				historic_command(t_env *e)
{
	if (K_UP(e))
	{
		if (e->cmd->next)
		{
			if (e->cmd->prev == NULL || ft_strcmp(&e->hist->cmd[e->q_pos], e->cmd->cmd))
				e->cmd->save = ft_strdup(&e->hist->cmd[e->q_pos]);
			e->cmd = e->cmd->next;
			aff_cmd(e);
		}
	}
	else if (K_DOWN(e))
	{
		if (e->cmd->prev)
		{
			if (ft_strcmp(&e->hist->cmd[e->q_pos], e->cmd->cmd))
				e->cmd->save = ft_strdup(&e->hist->cmd[e->q_pos]);
			e->cmd = e->cmd->prev;
			aff_cmd(e);
		}
	}
}
