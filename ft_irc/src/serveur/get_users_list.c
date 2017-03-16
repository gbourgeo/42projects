/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_users_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 02:16:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <fcntl.h>

static t_file		*new_user(char **str, t_file *next)
{
	int				len;
	t_file			*new;

	len = ft_tablen(str);
	if (len < 4 || len > 15 || sv_check_name_valid(str + 2))
		return (next);
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		ft_free(&str);
		return (next);
	}
	ft_strncpy(new->username, *str++, NICK_LEN);
	new->password = ft_strdup(*str++);
	ft_strncpy(new->nick, *str++, NICK_LEN);
	new->realname = ft_tabdup(str);
	new->next = next;
	return (new);
}

t_file				*get_users_list(void)
{
	int				fd;
	char			*buf;
	char			**str;
	t_file			*first;

	first = NULL;
	buf = NULL;
	if ((fd = open(USERS_FILE, O_RDONLY, 0644)) < 0)
	{
		ft_putstr_fd("Unable to open the users' file.", 2);
		return (NULL);
	}
	while (get_next_line(fd, &buf) > 0)
	{
		str = NULL;
		if (buf && *buf != '#' && (str = ft_strsplit(buf, ' ')))
			first = new_user(str, first);
		ft_free(&str);
		if (buf)
			free(buf);
		buf = NULL;
	}
	close(fd);
	return (first);
}
