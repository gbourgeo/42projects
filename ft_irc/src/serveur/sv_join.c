/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:26:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 04:22:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>
#include <time.h>

static void		sv_join_info(char *name, t_fd *cl)
{
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, "!~", 2, 0);
	send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
	send(cl->fd, "@", 1, 0);
	send(cl->fd, cl->addr, ADDR_LEN, 0);
	send(cl->fd, " JOIN ", 6, 0);
	send(cl->fd, name, ft_strlen(name), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static int		sv_channel_ident(char *name, t_chan *new, t_fd *cl, t_env *e)
{
	time_t		store;
	u_char		*ptr;
	char		*base;
	int			i[2];

	if (time(&store) == -1)
	{
		send(cl->fd, e->name, SERVER_LEN, 0);
		send(cl->fd, " ERROR ", 7, 0);
		send(cl->fd, cl->reg.nick, NICK_LEN, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, name, CHAN_LEN, 0);
		send(cl->fd, " :Server failed to create your channel", 38, 0);
		send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
		free(new);
		return (0);
	}
	ptr = (u_char *)&store;
	base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	if ((i[0] = ft_strlen(name)) > CHAN_LEN - 5)
		i[0] = CHAN_LEN - 5;
	i[1] = i[0] + 5;
	while (i[0] < i[1])
		new->name[i[0]++] = base[*ptr++ % 35];
	return (1);
}

/*
** Afficher les nouveaux mode du chan si on implemente la commande MODE
*/

static t_chan	*sv_new_chan(char *name, t_fd *cl, t_env *e)
{
	t_chan		*new;

	if ((new = (t_chan*)malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: Out of memory", e);
	new->prev = NULL;
	ft_strncpy(new->name, name, CHAN_LEN);
	if (*name == '!' && !sv_channel_ident(name, new, cl, e))
		return (e->chans);
	if (!*new->name)
		ft_bzero(new->topic, TOPIC_LEN + 1);
	ft_memset(&new->cmode, 0, sizeof(new->cmode));
	new->cmode |= (*new->name == '+') ? CHFL_TOPIC : CHFL_NOMSG | CHFL_SECRET;
	new->nbusers = 1;
	new->users = NULL;
	new->users = sv_add_usertochan(cl, new);
	if (*new->name == '!')
		new->users->mode |= USR_CREATOR;
	if (*new->name != '+')
		new->users->mode |= USR_CHANOP;
	new->next = e->chans;
	if (e->chans)
		e->chans->prev = new;
	return (new);
}

static int		sv_check_safe_chan(char *name, t_fd *cl, t_env *e)
{
	t_chan		*ch;
	int			len;

	ch = e->chans;
	while (ch)
	{
		len = ft_strlen(ch->name);
		if (*ch->name == '!' &&
			sv_strncmp(ch->name, name, len - 5) == ch->name[len - 5])
		{
			send(cl->fd, e->name, SERVER_LEN, 0);
			send(cl->fd, " ERROR ", 7, 0);
			send(cl->fd, cl->reg.nick, NICK_LEN, 0);
			send(cl->fd, " ", 1, 0);
			send(cl->fd, name, ft_strlen(name), 0);
			send(cl->fd, " :Short name for safe channel already in use", 44, 0);
			send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
			return (0);
		}
		ch = ch->next;
	}
	return (1);
}

static int		sv_join_channel(char *chan_name, t_fd *cl, t_env *e)
{
	t_chan		*chan;

	chan = e->chans;
	while (chan)
	{
		if (!sv_strcmp(chan_name, chan->name))
		{
			sv_join_info(chan->name, cl);
			chan->nbusers++;
			chan->users = sv_add_usertochan(cl, chan);
			cl->chans = sv_add_chantouser(chan, cl);
			return (1);
		}
		chan = chan->next;
	}
	if (*chan_name == '!' && !sv_check_safe_chan(chan_name, cl, e))
		return (0);
	e->chans = sv_new_chan(chan_name, cl, e);
	sv_join_info(e->chans->name, cl);
	cl->chans = sv_add_chantouser(e->chans, cl);
	if (*chan_name == '!')
		cl->chans->mode |= USR_CREATOR;
	else if (*chan_name != '+')
		cl->chans->mode |= USR_CHANOP;
	return (1);
}

static void		sv_leaveallchannels(t_fd *cl, t_env *e)
{
	t_listin	*next;

	next = cl->chans;
	while (next)
		next = next->next;
	(void)e;
}

/*
** Si on implemente /NAMES, l'appeler au lieu de /WHO.
*/

static void		sv_check_channels(char **cmds, t_env *e, t_fd *cl)
{
	char		**chans;
	char		*save;
	int			i;

	if ((chans = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: SERVER: out of memory", e);
	i = 0;
	if (!ft_strcmp("0", cmds[ft_tablen(cmds) - 1]) ||
		(!ft_strcmp("0", chans[i]) && ++i))
		sv_leaveallchannels(cl, e);
	while (chans[i])
	{
		if (!ISCHAN(*chans[i]) || !chans[i][1])
			sv_err(ERR_NOSUCHCHANNEL, chans[i], NULL, cl, e);
		else if (sv_join_channel(chans[i], cl, e))
		{
			save = cmds[1];
			cmds[1] = e->chans->name;
			sv_who(cmds, e, cl);
			cmds[1] = save;
		}
		i++;
	}
	ft_free(&chans);
}

void			sv_join(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(ERR_NEEDMOREPARAMS, "JOIN", NULL, cl, e));
	sv_check_channels(cmds, e, cl);
}
