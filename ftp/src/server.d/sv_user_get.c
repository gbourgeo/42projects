/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:43:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 15:58:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "sv_main.h"

static int	new_user(char *name, char *pass, t_user **next, t_env *env)
{
	t_user	*user;
	char	*ptr;

	if (!(user = ft_memalloc(sizeof(*user))))
		return (ERR_MALLOC);
	if (!(ptr = ft_strjoin(env->home, name)))
		return (ERR_MALLOC);
	user->home = ft_strjoin(ptr, "/");
	free(ptr);
	if (!user->home
	|| !(user->name = ft_strdup(name))
	|| !(user->pass = ft_strdup(pass)))
		return (ERR_MALLOC);
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
			else if (sv_user_parse(data, sv->info.env.home))
				errnb = new_user(data[0], data[1], &sv->users, &sv->info.env);
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
	if (access(SV_FILE_CLIENT, F_OK) < 0 || access(SV_FILE_CLIENT, R_OK) < 0)
		return (IS_OK);
	if ((fd = open(SV_FILE_CLIENT, O_RDONLY)) < 0)
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
	return (errnb);
}
