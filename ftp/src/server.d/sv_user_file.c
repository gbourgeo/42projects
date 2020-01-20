/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:43:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 20:09:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "sv_main.h"

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
				errnb = sv_new_user(data, &sv->users, sv);
			ft_tabdel(&data);
		}
	ft_tabdel(&array);
	return (errnb);
}

int			sv_user_file(t_server *sv)
{
	int		fd;
	int		errnb;
	char	*line;

	line = NULL;
	errnb = IS_OK;
	if (!FT_CHECK(sv->options, sv_user_mode))
		return (get_user("C:"SV_GUEST_NAME"::3:", sv));
	if (access(SV_USERS_FILE, F_OK) < 0 || access(SV_USERS_FILE, R_OK) < 0)
		return (ERR_OPEN);
	if ((fd = open(SV_USERS_FILE, O_RDONLY)) < 0)
		return (ERR_OPEN);
	while ((errnb = get_next_line(fd, &line)) > 0)
	{
		if ((errnb = get_user(line, sv)) != IS_OK)
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	if (errnb < 0)
		errnb = ERR_GETNEXTLINE;
	if (errnb == IS_OK)
		errnb = get_user("C:"SV_GUEST_NAME"::0:", sv);
	return (errnb);
}
