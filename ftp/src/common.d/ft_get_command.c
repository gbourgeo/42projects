/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 16:40:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 17:09:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "common.h"
#include "libft.h"

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (path)
		if (access(path, F_OK) == 0 && stat(path, &buffer) == 0)
			return (path);
	ft_strdel(&path);
	return (NULL);
}

char			*ft_get_command(char *cmd, char *paths, int n)
{
	char		**dirs;
	char		*tmp;
	char		*ret;
	int			i;

	dirs = NULL;
	tmp = NULL;
	ret = NULL;
	i = 0;
	if ((dirs = ft_strsplit(paths, ':')))
		while (dirs[i] && ret == NULL)
		{
			if ((tmp = ft_strjoin(dirs[i], "/")))
				ret = check_path(ft_strjoin(tmp, cmd + n));
			ft_strdel(&tmp);
			i++;
		}
	ft_freetab(&dirs);
	return (ret);
}
