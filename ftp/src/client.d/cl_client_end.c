/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 20:09:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 19:02:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <unistd.h>
#include "cl_main.h"

void			cl_ncurses_end(t_client *cl)
{
	if (cl->ncu.chatbox)
		delwin(cl->ncu.chatbox);
	if (cl->ncu.chatwin)
		delwin(cl->ncu.chatwin);
	if (cl->ncu.slistbox)
		delwin(cl->ncu.slistbox);
	if (cl->ncu.slistwin)
		delwin(cl->ncu.slistwin);
	if (cl->ncu.clistbox)
		delwin(cl->ncu.clistbox);
	if (cl->ncu.clistwin)
		delwin(cl->ncu.clistwin);
	if (cl->ncu.textbox)
		delwin(cl->ncu.textbox);
	if (cl->ncu.textwin)
		delwin(cl->ncu.textwin);
	endwin();
	ft_memset(&cl->ncu, 0, sizeof(cl->ncu));
}

t_cmd		*cl_precmd_end(t_cmd *cmd, int all)
{
	t_cmd	*next;

	if (!cmd)
		return (NULL);
	next = cmd->next;
	if (all)
		cl_precmd_end(next, 1);
	ft_tabdel(&cmd->code);
	free(cmd);
	return (next);
}

void			cl_client_end(t_client *cl)
{
	int		i;

	i = 0;
	ft_freestr(&cl->info.env.path);
	ft_freestr(&cl->info.env.home);
	while (i < NSIG)
	{
		if (cl->sig[i] != SIG_ERR)
			signal(i, cl->sig[i]);
		i++;
	}
	ft_close(&cl->server.fd_ctrl);
	cl_server_close(&cl->server, 1, cl);
	cl_precmd_end(cl->precmd, 1);
	cl_ncurses_end(cl);
}
