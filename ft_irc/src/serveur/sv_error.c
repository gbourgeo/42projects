/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 07:34:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 10:27:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_free_chan(t_chan **chan)
{
	t_chan		*ch;

	if (chan == NULL || *chan == NULL)
		return ;
	ch = *chan;
	if (ch->next)
		sv_free_chan(&ch->next);
	ft_memset(*chan, 0, sizeof(**chan));
	free(*chan);
	*chan = NULL;
}

static void		sv_free_users(t_file **file)
{
	t_file		*f;

	if (file == NULL || *file == NULL)
		return ;
	f = *file;
	if (f->next)
		sv_free_users(&f->next);
	if (f->password)
		free(f->password);
	ft_memset(*file, 0, sizeof(**file));
	free(*file);
	*file = NULL;
	close(e.fd);
}

static void		sv_free_fds(t_fd **fds)
{
	t_fd		*fd;

	if (fds == NULL || *fds == NULL)
		return ;
	fd = *fds;
	if ((*fds)->reg.password)
		add_in_userslist(e.users, *fds);
	if (fd->next)
		sv_free_fds(&fd->next);
	if (fd->reg.password)
		free(fd->reg.password);
	ft_free(&fd->reg.realname);
	if (fd->away)
		free(fd->away);
	ft_memset(*fds, 0, sizeof(**fds));
	free(*fds);
	*fds = NULL;
}

void			sv_error(char *str, t_env *e)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(str);
	while (e->fds && i < MAX_CLIENT)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			send(e->fds[i].fd, str, len, 0);
			send(e->fds[i].fd, END_CHECK, END_CHECK_LEN, 0);
		}
		close(e->fds[i].fd);
		i++;
	}
	sv_free_fds(&e->fds);
	sv_free_users(&e->users);
	sv_free_chan(&e->chans);
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	close(e->ipv4);
	close(e->ipv6);
	if (e->verb)
		ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
