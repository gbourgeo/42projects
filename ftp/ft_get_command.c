/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 16:40:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 17:20:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (access(path, F_OK) == 0 && stat(path, &buffer) == 0)
		return (path);
	free(path);
	return (NULL);
}

char			*ft_get_command(char *cmd, char **dirs, int n)
{
	char		*tmp;
	char		*ret;
	int			i;

	tmp = NULL;
	ret = NULL;
	i = 0;
	if (dirs == NULL)
	{
		ft_putendl("\033[31mERROR: ft_strsplit() failed.\033[0m");
		return (cmd);
	}
	while (dirs[i] && ret == NULL)
	{
		tmp = ft_strjoin(dirs[i], "/");
		ret = check_path(ft_strjoin(tmp, cmd + n));
		free(tmp);
		i++;
	}
	if (ret != NULL)
		free(cmd);
	ft_free(&dirs);
	return (ret);
}
