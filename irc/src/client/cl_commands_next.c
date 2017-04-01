/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 03:46:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 03:57:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

void			cl_nosuchcommand(char **cmds, t_client *cl)
{
	(void)cl;
	ft_putstr_fd(cmds[0], STDERR_FILENO);
	ft_putendl_fd(" :No such command.", STDERR_FILENO);
}

void			cl_pass(char **cmds, t_client *cl)
{
	if (!cmds[1] || !*cmds[1])
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putendl_fd(ERR_NEEDMOREPARAMS, STDERR_FILENO);
		return ;
	}
	if (cl->pass)
		free(cl->pass);
	cl->pass = ft_strdup(cmds[1]);
}

void			cl_user(char **cmds, t_client *cl)
{
	if (ft_tablen(cmds) < 4)
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		return (ft_putendl_fd(ERR_NEEDMOREPARAMS, STDERR_FILENO));
	}
	if (cl->user)
		ft_free(&cl->user);
	cl->user = ft_tabdup(&cmds[1]);
}
