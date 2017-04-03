/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_users_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/03 22:26:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <fcntl.h>

static void		add_in_userslist(t_file *cl, t_env *e)
{
	char		*nb;
	char		**ptr;

	write(e->fd, cl->nick, ft_strlen(cl->nick));
	write(e->fd, " ", 1);
	write(e->fd, cl->pass, ft_strlen(cl->pass));
	write(e->fd, " ", 1);
	write(e->fd, cl->username, ft_strlen(cl->username));
	write(e->fd, " ", 1);
	nb = ft_itoa(cl->umode);
	write(e->fd, nb, ft_strlen(nb));
	free(nb);
	ptr = cl->realname;
	while (ptr && *ptr)
	{
		write(e->fd, " ", 1);
		write(e->fd, *ptr, ft_strlen(*ptr));
		ptr++;
	}
	write(e->fd, "\n", 1);
}

void			update_users_file(t_env *e)
{
	t_file		*cl;
	t_file		*next;

	if ((e->fd = open(USERS_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		ft_putstr_fd("Users' file UPDATE failed", 2);
		return ;
	}
	cl = e->users;
	while (cl)
	{
		add_in_userslist(cl, e);
		next = cl->next;
		free(cl->pass);
		ft_free(&cl->realname);
		ft_memset(cl, 0, sizeof(*cl));
		free(cl);
		cl = NULL;
		cl = next;
	}
	close(e->fd);
}

static t_file	*new_user(char **str, t_file *next)
{
	int			len;
	t_file		*new;

	len = ft_tablen(str);
	if (len < 5 || len > 15 ||
		sv_check_name_valid(str[0]) || !ft_strisalnum(str[2]))
		return (next);
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		ft_free(&str);
		return (next);
	}
	ft_strncpy(new->nick, *str++, NICK_LEN);
	new->pass = ft_strdup(*str++);
	ft_strncpy(new->username, *str++, USERNAME_LEN);
	new->umode = ft_atoi(*str++);
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
	if ((e->fd = open(USERS_FILE, O_RDONLY, 0644)) < 0)
	{
		ft_putstr_fd("Unable to open the users' file", 2);
		return (NULL);
	}
	while (get_next_line(e->fd, &buf) > 0 || buf)
	{
		str = NULL;
		if (buf && *buf != '#' && (str = ft_strsplit(buf, ' ')))
			first = new_user(str, first);
		ft_free(&str);
		if (buf)
			free(buf);
		buf = NULL;
	}
	close(e->fd);
	return (first);
}
