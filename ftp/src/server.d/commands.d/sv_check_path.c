/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:08:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 02:47:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static char		*setup_path(char *path, char *pwd)
{
	char		*tmp;
	char		*ret;
	int			do_free;

	do_free = 0;
	if (pwd[ft_strlen(pwd) - 1] != '/')
	{
		if (!(tmp = ft_strjoin(pwd, "/")))
			return (NULL);
		do_free = 1;
	}
	else
		tmp = pwd;
	if (!(ret = ft_strjoin(tmp, path)))
		return (NULL);
	if (do_free)
		free(tmp);
	return (ret);
}

int				sv_check_path(char **path, t_client *cl, t_env *e)
{
	char		*pth;
	char		*tmp;
	int			do_setup;

	pth = *path;
	if (!pth || pth[0] == '-')
		return (IS_OK);
	do_setup = (pth[0] != '/');
	if (do_setup)
		if (!(pth = setup_path(*path, cl->pwd)))
			return (ERR_MALLOC);
	pth = sv_recreate_path(pth);
	if (e->home[ft_strlen(e->home) - 1] != '/')
		tmp = ft_strjoin(e->home, pth);
	else
		tmp = ft_strjoin(e->home, pth + 1);
	if (do_setup)
		free(pth);
	if (!tmp)
		return (ERR_MALLOC);
	free(*path);
	*path = tmp;
	return (IS_OK);
}
