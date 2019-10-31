/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:53:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 16:46:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int			parse_type(char *type)
{
	if (ft_strlen(type) != 1 || !ft_strcset(type, "CS"))
		return (0);
	return (1);
}

static int			parse_name(char *name)
{
	if (!name)
		return (0);
	while (*name)
		if (!ft_isalnum(*name))
			return (0);
		else
			++name;
	return (1);
}

static int			parse_rights(char *rights)
{
	if (rights)
	{
		while (*rights)
			if (!ft_isdigit(*rights))
				return (0);
			else
				++rights;
	}
	return (1);
}

int					sv_user_parse(char **data, const char *home)
{
	int				i;
	char			*newdir;
	struct stat		buf;

	i = 0;
	if (parse_type(data[0]))
		if (parse_name(data[1]))
			if (parse_rights(data[2]))
				return (1);
	return (0);
	if (!(newdir = ft_strjoin(home, data[0])))
		return (0);
	i = 1;
	if (access(newdir, F_OK) < 0)
	{
		if (mkdir(newdir, 0777) < 0)
			i = 0;
	}
	else if (access(newdir, R_OK) < 0 || access(newdir, W_OK) < 0
	|| stat(newdir, &buf) < 0 || !S_ISDIR(buf.st_mode))
		i = 0;
	ft_strdel(&newdir);
	return (i);
}
