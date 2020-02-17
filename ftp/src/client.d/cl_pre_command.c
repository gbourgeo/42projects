/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pre_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:24:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/17 05:35:26 by gbourgeo         ###   ########.fr       */
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

static char		**cl_new_code(char *code[])
{
	char		**ret;
	int			len;

	len = ft_tablen(code);
	ret = ft_memalloc(sizeof(*ret) * (len + 1));
	while (ret && len--)
		if (!(ret[len] = ft_strdup(code[len])))
			ft_tabdel(&ret);
	return (ret);
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
	if (!(cmd->code = cl_new_code(code)))
	{
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
	(char *[]){ "212 ", NULL }, *cmds))
	&& (*cmds = cl_new_command("NLST", cl->ncu.slistwin,
	(char *[]){ "220 ", "227 ", NULL }, *cmds)))
	{
		if (sv->pass
		&& (*cmds = cl_new_command("PASS ", cl->ncu.chatwin,
		(char *[]){ "331 ", NULL, }, *cmds)))
		{
			ft_tabdel(&(*cmds)->next->code);
			(*cmds)->next->code = cl_new_code((char *[]){ "", "227 ", NULL });
			cl_ring_write(sv->pass, &(*cmds)->wr);
			if (sv->user
			&& (*cmds = cl_new_command("USER ", cl->ncu.chatwin,
			(char *[]){ "220 ", NULL }, *cmds)))
				cl_ring_write(sv->user, &(*cmds)->wr);
		}
		return (IS_OK);
	}
	return (ERR_MALLOC);
}

t_cmd			*cl_pre_cmd_exec(t_cmd *cmds, t_server *sv, t_client *cl)
{
	int			i;

	if (cmds == NULL)
	{
		cl->printtowin = cl->ncu.chatwin;
		return (NULL);
	}
	i = cmds->nb_response;
	if (cmds->nb_response == ft_tablen(cmds->code))
		return (cl_precmd_end(cmds, 0));
	if (!cmds->code[i][0] || is_valid_response(sv->response))
	{
		if (cmds->code[i][0] && sv->response[0] - cmds->code[i][0] > 0)
			return (cl_precmd_end(cmds, 0));
		ft_strclr(sv->response);
		if (cmds->printtowin != cl->ncu.chatwin)
			wclear(cmds->printtowin);
		cl->printtowin = cmds->printtowin;
		cl_lf(&cmds->wr, cl);
		++cmds->nb_response;
	}
	return (cmds);
}
