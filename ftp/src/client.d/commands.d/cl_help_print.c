/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_help_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 22:57:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/17 02:27:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_help_print(t_command *cmd, char *args, char **descrip,
t_client *cl)
{
	int			i;
	int			err;

	i = 0;
	if ((err = wprintw(cl->ncu.chatwin, "Command: %s - %s\n",
	cmd->name, cmd->descrip)) == OK
	&& (err = wprintw(cl->ncu.chatwin, "\nUsage: %s %s\n",
	cmd->name, args)) == OK)
		while (descrip[i] && err == OK)
		{
			err = wprintw(cl->ncu.chatwin, "\t%s\n", descrip[i]);
			i++;
		}
	wrefresh(cl->ncu.chatwin);
	return ((err == OK) ? IS_OK : ERR_WRITE);
}
