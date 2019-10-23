/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mkdir_rmdir_unlink.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/23 23:32:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
/*
int					sv_unlink(char **cmds, t_server *sv)
{
	int				i;
	char			*file;
	char			*path;

	i = 1;
	sv->rec = 0;
	while (cmds[i] && sv->rec == 0)
	{
		if ((file = ft_get_path(cmds[i], "/", sv->pwd, sv->oldpwd)) == NULL)
			sv->rec = file_error("\2ERROR: server: get_path()", sv, SERVER, 1);
		else if ((path = ft_strjoin(sv->home, file)) == NULL)
			sv->rec = file_error("\2ERROR: server: no memory.", sv, SERVER, 1);
		else if (unlink(path) == -1)
			sv->rec = file_error("\2ERROR: Can't remove that.", sv, SERVER, 1);
		if (file)
			free(file);
		if (path)
			free(path);
		i++;
	}
	if (sv->rec == 0)
		send(sv->fd, "\033[32mSUCCESS\033[0m\n", 17, 0);
	return (sv->rec);
}
*/