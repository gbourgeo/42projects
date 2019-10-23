/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:08:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/20 17:58:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static char		*search_back(char *head, char *path)
{
	if (head > path)
		--head;
	while (head > path && *head != '/')
		--head;
	return (head);
}

static char		*recreate_path(char *path)
{
	char		*head;
	char		*tail;

	head = path;
	while (*head)
	{
		if (!(tail = ft_strchr(head + 1, '/')))
			tail = head + ft_strlen(head);
		if (!ft_strncmp(head + 1, ".", tail - head - 1))
			head = ft_strcpy(head, tail);
		else if (!ft_strncmp(head + 1, "..", tail - head - 1))
		{
			if ((head = search_back(head, path)))
				head = ft_strcpy(head, tail);
		}
		else
			head = tail;
	}
	if (!*path)
		ft_strcpy(path, "/");
	return (path);
}

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
	pth = recreate_path(pth);
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
