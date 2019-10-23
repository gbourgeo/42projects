/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 18:37:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 15:43:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

static char		*join_pwd(char *path, char *pwd)
{
	char		*tmp;

	if (pwd[ft_strlen(pwd) - 1] == '/')
		tmp = ft_strdup(pwd);
	else
		tmp = ft_strjoin(pwd, "/");
	free(pwd);
	pwd = ft_strjoin(tmp, path);
	free(tmp);
	return (pwd);
}

static char		*decrypt_path(char *pwd, char **path)
{
	int			i;

	i = 0;
	if (!ft_strcmp("~", path[i]))
	{
		free(pwd);
		pwd = ft_strdup("/");
		i++;
	}
	while (path[i])
	{
		if (!ft_strcmp("..", path[i]))
			ft_strclr(ft_strrchr(pwd, '/'));
		else if (ft_strcmp(".", path[i]))
			pwd = join_pwd(path[i], pwd);
		i++;
	}
	return (pwd);
}

char			*ft_get_path(char *dest, char *home, char *lpwd, char *oldpwd)
{
	char		**path;
	char		*pwd;

	pwd = NULL;
	path = NULL;
	if (!dest || dest[0] == '\0')
		pwd = ft_strdup(home);
	else if (dest[0] == '/')
		pwd = ft_strdup(dest);
	else if ((pwd = ft_strdup(lpwd)) == NULL)
		return (NULL);
	else if ((path = ft_strsplit(dest, '/')) == NULL)
		return (NULL);
	else if (!ft_strcmp("--", path[0]))
		pwd = ft_strdup(home);
	else if (!ft_strcmp("-", path[0]))
		pwd = ft_strdup(oldpwd);
	else
		pwd = decrypt_path(pwd, path);
	ft_freetab(&path);
	return (pwd);
}
