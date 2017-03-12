/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_users_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 05:23:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <fcntl.h>

static t_file		*free_str(char **str, t_file *ret)
{
	while (str && *str != NULL)
		free(*str++);
	return (ret);
}

static t_file		*new_user(char **str, t_file *next)
{
	t_file			*new;

	if (str[0] == NULL || str[1] == NULL)
	{
		if (str[0])
			free(str[0]);
		return (next);
	}
	if (sv_check_name_valid(str))
		return (free_str(str, next));
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		ft_free(&str);
		return (next);
	}
	ft_strncpy(new->login, *str, NICK_LEN);
	free(*str);
	str++;
	new->password = *str++;
	new->next = next;
	return (free_str(str, new));
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
		if (buf && *buf != '#' && (str = ft_strsplit(buf,' ')))
			first = new_user(str, first);
		if (str)
			free(str);
		if (buf)
			free(buf);
		buf = NULL;
	}
	close(fd);
	return (first);
}
