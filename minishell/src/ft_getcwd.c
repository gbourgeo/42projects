/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 06:07:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/28 11:57:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char			*ft_getcwd(char *dir, char **env)
{
	char		*pwd;
	char		*tmp;
	int			buf;

	tmp = ft_getenv("PWD", env);
	buf = ft_strlen(tmp) + ft_strlen(dir);
	pwd = NULL;
	if (tmp == NULL)
		return (NULL);
	if ((pwd = getcwd(pwd, buf)) == NULL)
		ft_putendl("42sh: Error with getcwd.");
	return (pwd);
}
