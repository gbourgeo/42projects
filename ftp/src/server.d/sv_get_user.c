/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_get_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:43:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/25 23:41:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "sv_main.h"

static int	sv_new_user(char *name, char *pass, t_user **next)
{
	t_user	*user;

	if (!(user = ft_memalloc(sizeof(*user))))
		return (ERR_MALLOC);
	user->name = ft_strdup(name);
	user->pass = ft_strdup(pass);
	user->next = *next;
	*next = user;
	return (IS_OK);
}

static int	get_user(char *line, t_server *sv)
{
	char	**array;
	char	**data;
	int		errnb;

	errnb = IS_OK;
	if (!(array = ft_split_whitespaces(line)))
		return (ERR_MALLOC);
	if (ft_tablen(array))
		if (array[0][0] != '#')
		{
			if (!(data = ft_strsplit(array[0], ':')))
				errnb = ERR_MALLOC;
			else if (ft_tablen(data) > 1)
				errnb = sv_new_user(data[0], data[1], &sv->users);
			ft_freetab(&data);
		}
	ft_freetab(&array);
	return (errnb);
}

int			sv_get_user(t_server *sv)
{
	int		fd;
	char	*line;
	int		errnb;

	errnb = IS_OK;
	if (access(SV_FILE_CLIENT, F_OK) < 0 || access(SV_FILE_CLIENT, R_OK) < 0)
		return (IS_OK);
	if ((fd = open(SV_FILE_CLIENT, O_RDONLY)) < 0)
		return (ERR_OPEN);
	while ((errnb = get_next_line(fd, &line)) > 0)
	{
		if (!line)
			continue ;
		if ((errnb = get_user(line, sv)) != IS_OK)
			break ;
		ft_strdel(&line);
	}
	close(fd);
	return (errnb);
}
