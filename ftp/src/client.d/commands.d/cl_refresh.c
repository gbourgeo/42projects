/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_refresh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:03:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 17:54:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int					cl_refresh(char *buf, char **cmd, t_client *cl)
{
	(void)buf;
	(void)cmd;
	wprintw(cl->ncu.chatwin, "Refreshing...\n");
	wrefresh(cl->ncu.chatwin);
	cl->precmd = cl_new_command("\\ls -ap", cl->ncu.clistwin,
	(char *[]){ "", "" }, cl->precmd);
	cl->precmd = cl_new_command("NLST", cl->ncu.slistwin,
	(char *[]){ "", "22" }, cl->precmd);
	return (IS_OK);
}

int					cl_refresh_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the client to refresh the \"Server List\"",
		"Window and the \"Client List\" Window.", NULL
	};

	return (cl_help_print(cmd, "", help, cl));
}
