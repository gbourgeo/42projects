/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:43:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/26 17:13:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static int		sv_check_if_valid(char **cmds, t_fd *cl)
{
	char		*tmp;

	if (!cmds[1])
		return (1);
	if (*cmds[1] == '-' || ft_isdigit(*cmds[1]) ||
		!ft_strncmp(cmds[1], "anonymous", NAME_SIZE))
		return (2);
	tmp = cmds[1];
	while (*tmp && tmp - cmds[1] < NAME_SIZE)
	{
		if (!ISVALID(*tmp) || *tmp == ' ')
			break ;
		tmp++;
	}
	*tmp = '\0';
	if (!*cmds[1] || !ft_strncmp(cmds[1], cl->nick, NAME_SIZE))
		return (2);
	return (0);
}

void			sv_nick(char **cmds, t_env *e, t_fd *cl)
{
	int			err;
	t_user		*us;

	err = sv_check_if_valid(cmds, cl);
	if (err == 1)
		return (sv_err(cmds[0], ":No nickname given", cl->fd));		
	if (err == 2)
		return (sv_err(cmds[1], ":Erroneus Nickname", cl->fd));
	if (cl->chan)
	{
		us = cl->chan->user;
		while (us)
		{
			if (((t_fd *)us->is)->fd != cl->fd &&
				!ft_strncmp(cmds[1], ((t_fd *)us->is)->nick, NAME_SIZE))
				return (sv_err(cmds[1], ":Nick already in use", cl->fd));
			us = us->next;
		}
	}
	if (++cl->wr.head == cl->wr.end)
		cl->wr.head = cl->wr.start;
	sv_sendto_chan(cl);
	ft_strncpy(cl->nick, cmds[1], NAME_SIZE);
	(void)e;
}
