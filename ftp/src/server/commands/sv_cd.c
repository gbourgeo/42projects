/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 14:18:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/30 20:42:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_free(char *tmp, char *tmp2)
{
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
}

int				sv_cd(char **args, t_envi *e)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = NULL;
	if ((tmp = ft_get_path(args[1], "/", e->pwd, e->oldpwd)) == NULL)
		return (file_error("\2 ERROR: get_path() failed", e, SERVER, 1));
	else if ((tmp2 = ft_strjoin(e->home, tmp)) == NULL)
		return (file_error("\2 ERROR: lack of memory", e, SERVER, 1));
	else if (chdir(tmp2) == -1)
		return (file_error("\2 ERROR: cd : permission denied.", e, SERVER, 1));
	free(e->oldpwd);
	e->oldpwd = e->pwd;
	e->pwd = ft_strdup(tmp);
	if (e->pwd[0])
		send(e->fd, e->pwd, ft_strlen(e->pwd), 0);
	else
		send(e->fd, "/", 1, 0);
	send(e->fd, "\1\033[32mSUCCESS\033[0m\n", 19, 0);
	sv_free(tmp, tmp2);
	return (0);
}
