/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 05:35:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 00:31:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		*ft_getenv(char *path, char **environ)
{
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strcmp(environ[i], path) == 0)
			return (environ[i] + ft_strlen(path));
		i++;
	}
	return (NULL);
}

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (access(path, F_OK) == 0 && stat(path, &buffer) == 0)
		return (path);
	return (NULL);
}

char			*ft_get_path_from(char *path, t_env *e)
{
	int			i;
	int			j;
	char		*base;

	i = 0;
	if (*e->cmd[0] == '/')
		return (ft_strcpy(path, e->cmd[0]));
	if (*e->cmd[0] == '.' || *e->cmd[0] == '~')
		return (ft_strcpy(path, e->cmd[0]));
	base = ft_getenv("PATH=", e->environ);
	if (base == NULL)
		base = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin";
	while (base[i])
	{
		j = 0;
		ft_strclr(path);
		while (base[i] && base[i] != ':')
			path[j++] = base[i++];
		path = ft_strcat(path, "/");
		path = ft_strcat(path, e->cmd[0]);
		if (check_path(path))
			return (path);
		i = (base[i] == ':') ? i + 1 : i;
	}
	return (ft_strcpy(path, e->cmd[0]));
}
