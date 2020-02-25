/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pre_command_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:46:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:29:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static t_cmd	*handle_precode(t_cmd *cmds, t_server *sv, t_client *cl)
{
	if (!cmds->precode[0])
	{
		ft_strdel(&cmds->precode);
		if ((cl->printtowin = cmds->printtowin) != cl->ncu.chatwin)
			wclear(cmds->printtowin);
		cl->verbose = FT_CHECK(cl->options, cl_verbose);
		cl_client_commands(&cmds->wr, cl);
	}
	else if (is_valid_response(sv->response))
	{
		if (sv->response[0] - cmds->precode[0] > 0)
			return (cl_precmd_end(cmds, 0, cl));
		ft_strclr(sv->response);
		ft_strcpy(&cmds->precode[0], &cmds->precode[1]);
	}
	return (cmds);
}

static t_cmd	*handle_code(t_cmd *cmds, t_server *sv, t_client *cl)
{
	if (!cmds->code[0])
		ft_strdel(&cmds->code);
	else if (is_valid_response(sv->response))
	{
		if (sv->response[0] - cmds->code[0] > 0)
			return (cl_precmd_end(cmds, 0, cl));
		ft_strclr(sv->response);
		ft_strcpy(&cmds->code[0], &cmds->code[1]);
	}
	return (cmds);
}

t_cmd			*cl_pre_cmd_exec(t_cmd *cmds, t_server *sv, t_client *cl)
{
	if (cmds == NULL)
		return (cmds);
	if (cmds->precode)
		cmds = handle_precode(cmds, sv, cl);
	else if (cmds->code)
		cmds = handle_code(cmds, sv, cl);
	else
		return (cl_precmd_end(cmds, 0, cl));
	return (cmds);
}
