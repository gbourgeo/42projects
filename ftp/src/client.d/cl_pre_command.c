/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pre_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:24:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 17:52:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include "cl_struct.h"

static void		cl_ring_write(const char *cmd, t_buff *ring)
{
	int		i;

	i = 0;
	if (cmd)
		while (cmd[i] && ring->len < (int)sizeof(ring->buff) - 1)
		{
			*ring->tail++ = cmd[i++];
			ring->len++;
		}
}

t_cmd			*cl_new_command(const char *name, WINDOW *win, char *codes[],
t_cmd *next)
{
	t_cmd		*cmd;

	if (!(cmd = ft_memalloc(sizeof(*cmd))))
		return (next);
	cmd->wr.head = cmd->wr.buff;
	cmd->wr.tail = cmd->wr.buff;
	cl_ring_write(name, &cmd->wr);
	cmd->printtowin = win;
	if (!(cmd->precode = ft_strdup(codes[0]))
	|| !(cmd->code = ft_strdup(codes[1])))
	{
		cl_precmd_end(cmd, 0, NULL);
		return (next);
	}
	cmd->next = next;
	wclear(win);
	wrefresh(win);
	return (cmd);
}

int				cl_pre_command(t_cmd **cmds, t_server *sv, t_client *cl)
{
	*cmds = NULL;
	if ((*cmds = cl_new_command("\\ls -ap", cl->ncu.clistwin,
		(char *[]){ "", "" }, *cmds))
	&& (*cmds = cl_new_command("NLST", cl->ncu.slistwin,
		(char *[]){ "2", "22" }, *cmds)))
	{
		if (sv->pass
		&& (*cmds = cl_new_command("PASS ", cl->ncu.chatwin,
			(char *[]){ "", "2" }, *cmds)))
		{
			ft_strdel(&(*cmds)->next->precode);
			(*cmds)->next->precode = ft_strdup("");
			ft_strdel(&(*cmds)->next->code);
			(*cmds)->next->code = ft_strdup("22");
			cl_ring_write(sv->pass, &(*cmds)->wr);
		}
		if (sv->user
		&& (*cmds = cl_new_command("USER ", cl->ncu.chatwin,
			(char *[]){ "2", "3" }, *cmds)))
			cl_ring_write(sv->user, &(*cmds)->wr);
		return (IS_OK);
	}
	return (ERR_MALLOC);
}
