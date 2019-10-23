/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:40:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/23 18:56:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sv_main.h"

static int		mkdir_opts(char **cmds, int *options, int *i)
{
	int		j;

	*options = 0;
	*i = 1;
	while (cmds[*i] && cmds[*i][0] == '-')
	{
		j = 0;
		while (cmds[*i][++j])
			if (cmds[*i][j] == 'p')
				*options |= (1 << 0);
			else if (cmds[*i][j] == 'v')
				*options |= (1 << 1);
			else
				return (ERR_WRONG_PARAM);
		(*i)++;
	}
	return ((cmds[*i] && cmds[*i][0]) ? IS_OK : ERR_NB_PARAMS);
}

static int		mkdir_create(char *path, int *opt, t_client *cl, t_server *sv)
{
	char		*ptr;
	int			errnb;

	if (!(ptr = ft_strdup(path)))
		return (ERR_MALLOC);
	if ((errnb = sv_check_path(&ptr, cl, &sv->info.env)))
		return (errnb);
	if ((errnb = mkdir(ptr, 0777)) != 0 && !(*opt & (1 << 0)))
		*opt |= (1 << 7);
	free(ptr);
	if (errnb == 0 && !(*opt & (1 << 0)) && (*opt & (1 << 1)))
		ptr = "created directory: ";
	else if (errnb != 0 && !(*opt & (1 << 0)))
		ptr = "failed to create: ";
	else
		ptr = NULL;
	errnb = IS_OK;
	if (ptr)
		if ((errnb = sv_client_write("mkdir: ", cl)) == IS_OK)
			if ((errnb = sv_client_write(ptr, cl)) == IS_OK)
				if ((errnb = sv_client_write(path, cl)) == IS_OK)
					errnb = sv_client_write("\n", cl);
	return (errnb);
}

int				sv_mkdir(char **cmds, t_client *cl, t_server *sv)
{
	int		i;
	int		opt;
	int		errnb;
	char	*dir;

	if ((errnb = mkdir_opts(cmds, &opt, &i)) != IS_OK)
		return (sv_client_write(ft_get_error(errnb), cl));
	while (cmds[i])
	{
		dir = (cmds[i][0] == '/') ? cmds[i] + 1 : cmds[i];
		if (opt & (1 << 0))
			while (*dir && (dir = ft_strchr(dir, '/')) && *(dir + 1))
			{
				*dir = '\0';
				if ((errnb = mkdir_create(cmds[i], &opt, cl, sv)) != IS_OK)
					return (errnb);
				*dir++ = '/';
			}
		if ((errnb = mkdir_create(cmds[i], &opt, cl, sv)) != IS_OK)
			return (errnb);
		i++;
	}
	if (opt & (1 << 7))
		return (sv_client_write(SERVER_ERR_OUTPUT, cl));
	return (sv_client_write(SERVER_OK_OUTPUT, cl));
}
