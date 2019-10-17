/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 16:40:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 00:01:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (path)
		if (access(path, F_OK) == 0 && stat(path, &buffer) == 0)
			return (path);
	if (path)
		free(path);
	return (NULL);
}

char			*ft_get_command(char *cmd, char *paths, int n)
{
	char		**dirs;
	char		*tmp;
	char		*ret;
	int			i;

	tmp = NULL;
	ret = NULL;
	i = 0;
	if ((dirs = ft_strsplit(paths, ':')))
		while (dirs[i] && ret == NULL)
		{
			if (!(tmp = ft_strjoin(dirs[i], "/")))
				break ;
			ret = check_path(ft_strjoin(tmp, cmd + n));
			free(tmp);
			i++;
		}
	ft_freetab(&dirs);
	return (ret);
}
