/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pre_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:24:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 00:47:40 by gbourgeo         ###   ########.fr       */
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

t_cmd			*cl_new_command(const char *name, WINDOW *win, char *code[],
t_cmd *next)
{
	t_cmd		*cmd;

	if (!(cmd = ft_memalloc(sizeof(*cmd))))
		return (next);
	cmd->wr.head = cmd->wr.buff;
	cmd->wr.tail = cmd->wr.buff;
	cl_ring_write(name, &cmd->wr);
	cmd->printtowin = win;
	if (!(cmd->code = ft_memalloc(sizeof(*cmd->code) * 3))
	|| !(cmd->code[0] = ft_strdup(code[0]))
	|| !(cmd->code[1] = ft_strdup(code[1])))
	{
		ft_tabdel(&cmd->code);
		free(cmd);
		return (next);
	}
	cmd->nb_response = 0;
	cmd->next = next;
	return (cmd);
}

int				cl_pre_command(t_cmd **cmds, t_server *sv, t_client *cl)
{
	*cmds = NULL;
	if ((*cmds = cl_new_command("\\ls -p", cl->ncu.clistwin,
	(char *[]){ "212 ", "" }, *cmds))
	&& (*cmds = cl_new_command("NLST", cl->ncu.slistwin,
	(char *[]){ "220 ", "227 " }, *cmds)))
	{
		if (sv->pass
		&& (*cmds = cl_new_command("PASS ", cl->ncu.chatwin,
		(char *[]){ "331 ", "" }, *cmds)))
		{
			(*cmds)->next->code = (char *[]){ "227 ", "" };
			cl_ring_write(sv->pass, &(*cmds)->wr);
			if (sv->user
			&& (*cmds = cl_new_command("USER ", cl->ncu.chatwin,
			(char *[]){ "220 ", "" }, *cmds)))
				cl_ring_write(sv->user, &(*cmds)->wr);
		}
		return (IS_OK);
	}
	return (ERR_MALLOC);
}

static int		is_valid_response(char *res)
{
	return (ft_isdigit(res[0]) && ft_isdigit(res[1]) && ft_isdigit(res[2])
	&& res[3] == ' ');
}

t_cmd			*cl_pre_cmd_exec(t_cmd *cmds, t_server *sv, t_client *cl)
{
	t_cmd		*next;
	int			i;

	if ((next = cmds) != NULL)
	{
		i = cmds->nb_response;
		if (cmds->nb_response == 2 || !cmds->code[i][0])
		{
			next = cmds->next;
			cl_precmd_end(cmds, 0);
		}
		else if (is_valid_response(sv->response))
		{
			if (ft_strncmp(sv->response, cmds->code[i], 4) > cmds->code[i][0])
			{
				cmds->printtowin = cl->ncu.chatwin;
				cl_precmd_end(cmds, 0);
				return (NULL);
			}
			ft_strclr(sv->response);
			if (cmds->printtowin != cl->ncu.chatwin)
				wclear(cmds->printtowin);
			cl->printtowin = cmds->printtowin;
			cl_lf(&cmds->wr, cl);
			++cmds->nb_response;
		}
	}
	return (next);
}
