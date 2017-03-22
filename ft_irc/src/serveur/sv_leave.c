/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:37:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 20:47:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		check_normal_channel(char *name, char **cmd, t_fd *cl, t_env *e)
{
	t_chan		*chan;

	chan = e->chans;
	while (chan && sv_strcmp(name, chan->name))
		chan = chan->next;
	if (chan == NULL)
		sv_err(ERR_NOSUCHCHANNEL, name, NULL, cl);
	else
		sv_find_userinchan(cmd, chan, cl);
}

static void		check_safe_channel(char *name, char **cmd, t_fd *cl, t_env *e)
{
	t_chan		*chan;
	t_chan		*found;
	int			len;

	found = NULL;
	chan = e->chans;
	while (chan)
	{
		len = ft_strlen(chan->name);
		if (sv_strncmp(chan->name, name, len - 5) == chan->name[len - 5])
		{
			if (found)
				break ;
			found = chan;
		}
		chan = chan->next;
	}
	if (found && chan)
		sv_err(ERR_TOOMANYTARGETS, name, NULL, cl);
	else if (chan == NULL && found == NULL)
		sv_err(ERR_NOSUCHCHANNEL, name, NULL, cl);
	else
		sv_find_userinchan(cmd, found, cl);
}

void			sv_leave(char **cmds, t_env *e, t_fd *cl)
{
	char		**list;
	int			i;

	if (!cmds[0] || *cmds[0] == '\0')
		return (sv_err(ERR_NEEDMOREPARAMS, "LEAVE", NULL, cl));
	if ((list = ft_strsplit(cmds[0], ',')) == NULL)
		sv_error("ERROR: SERVER: Out of memory", e);
	i = 0;
	while (list[i])
	{
		if (*list[i] == '!')
			check_safe_channel(list[i], cmds + 1, cl, e);
		else
			check_normal_channel(list[i], cmds + 1, cl, e);
		i++;
	}
	ft_free(&list);
}
