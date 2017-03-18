/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_users_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/18 03:46:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <fcntl.h>

t_file			*add_in_users(t_file *users, t_fd *cl)
{
	t_file		*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (users);
	ft_strncpy(new->username, cl->reg.username, USERNAME_LEN);
	new->password = cl->reg.password;
	cl->reg.password = NULL;
	ft_strncpy(new->nick, cl->reg.nick, NICK_LEN);
	new->realname = cl->reg.realname;
	cl->reg.realname = NULL;
	new->next = users;
	return (new);
}

void			add_in_userslist(t_file *users, t_fd *cl)
{
	char		*nb;
	char		**ptr;

	while (users)
	{
		if (!ft_strcmp(users->username, cl->reg.username))
			return ;
		users = users->next;
	}
	write(e.fd, cl->reg.username, ft_strlen(cl->reg.username));
	write(e.fd, " ", 1);
	write(e.fd, cl->reg.password, ft_strlen(cl->reg.password));
	write(e.fd, " ", 1);
	nb = ft_itoa(cl->reg.umode);
	write(e.fd, nb, ft_strlen(nb));
	free(nb);
	write(e.fd, " ", 1);
	write(e.fd, cl->reg.nick, ft_strlen(cl->reg.nick));
	ptr = cl->reg.realname;
	while (ptr && *ptr++)
	{
		write(e.fd, " ", 1);
		write(e.fd, *(ptr - 1), ft_strlen(*(ptr - 1)));
	}
	write(e.fd, "\n", 1);
}

void			update_users_file(t_env *e)
{
	t_fd		*cl;

	cl = e->fds;
	while (cl)
	{
		if (cl->reg.password)
			add_in_userslist(e->users, cl);
		cl = cl->next;
	}
	close(e->fd);
}

static t_file	*new_user(char **str, t_file *next)
{
	int			len;
	t_file		*new;

	len = ft_tablen(str);
	if (len < 5 || len > 15 || sv_check_name_valid(str[3]))
		return (next);
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		ft_free(&str);
		return (next);
	}
	ft_strncpy(new->username, *str++, USERNAME_LEN);
	new->password = ft_strdup(*str++);
	new->mode = ft_atoi(*str++);
	ft_strncpy(new->nick, *str++, NICK_LEN);
	new->realname = ft_tabdup(str);
	new->next = next;
	return (new);
}

t_file			*get_users_list(t_env *e)
{
	char		*buf;
	char		**str;
	t_file		*first;

	first = NULL;
	buf = NULL;
	if ((e->fd = open(USERS_FILE, O_RDWR | O_CREAT | O_APPEND, 0644)) < 0)
	{
		ft_putstr_fd("Unable to open the users' file.", 2);
		return (NULL);
	}
	while (get_next_line(e->fd, &buf) > 0)
	{
		str = NULL;
		if (buf && *buf != '#' && (str = ft_strsplit(buf, ' ')))
			first = new_user(str, first);
		ft_free(&str);
		if (buf)
			free(buf);
		buf = NULL;
	}
	return (first);
}
