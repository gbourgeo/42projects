/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:43:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/24 23:49:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "sv_main.h"

static int	new_user(char **data, t_user **next, t_server *sv)
{
	t_user	*user;
	char	*ptr;

	if (!(user = ft_memalloc(sizeof(*user))))
		return (ERR_MALLOC);
	user->type = (data[0][0] == 'S') ? SERVER_TYPE : CLIENT_TYPE;
	if (sv->options & (1 << sv_create_dir))
	{
		if (!(ptr = ft_strjoin(sv->info.env.home, data[1])))
			return (ERR_MALLOC);
		user->home = ft_strjoin(ptr, "/");
		free(ptr);
	}
	else
		user->home = ft_strdup(sv->info.env.home);
	if (!user->home
	|| !(user->name = ft_strdup(data[1]))
	|| !(user->pass = ft_strdup(data[2])))
		return (ERR_MALLOC);
	if ((user->rights = ft_atoi(data[3])) < 0)
		user->rights = 0;
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
			if (!(data = ft_strsplit2(array[0], ':')))
				errnb = ERR_MALLOC;
			else if (sv_user_parse(data, sv))
				errnb = new_user(data, &sv->users, sv);
			ft_freetab(&data);
		}
	ft_freetab(&array);
	return (errnb);
}

int			sv_user_get(t_server *sv)
{
	int		fd;
	char	*line;
	int		errnb;

	errnb = IS_OK;
	if (!SV_CHECK(sv->options, sv_user_mode))
		return (IS_OK);
	if (access(SV_USERS_FILE, F_OK) < 0 || access(SV_USERS_FILE, R_OK) < 0)
		return (IS_OK);
	if ((fd = open(SV_USERS_FILE, O_RDONLY)) < 0)
		return (ERR_OPEN);
	line = NULL;
	while ((errnb = get_next_line(fd, &line)) > 0)
	{
		if (!line)
			continue ;
		if ((errnb = get_user(line, sv)) != IS_OK)
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	if (errnb == IS_OK)
		errnb = get_user("C:"SV_GUEST_NAME"::1:", sv);
	return (errnb);
}
