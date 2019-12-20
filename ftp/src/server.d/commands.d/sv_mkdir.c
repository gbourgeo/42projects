/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:40:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 17:44:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sv_main.h"

/*
** MKDIR options are:
**	-p		Create parent directories without error if they exist
**	-v		Print a message for each directory created
*/
#define MKDIR_P		1
#define MKDIR_V		2
#define MKDIR_ERR	128

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
				*options |= MKDIR_P;
			else if (cmds[*i][j] == 'v')
				*options |= MKDIR_V;
			else
				return (ERR_WRONG_PARAM);
		(*i)++;
	}
	return ((cmds[*i] && cmds[*i][0]) ? IS_OK : ERR_NB_PARAMS);
}

static int		mkdir_create(t_mkdir *mk, t_client *cl, t_server *sv)
{
	char		*ptr;
	int			errnb;

	(void)sv;
	if (!(ptr = ft_strdup(mk->cmd[mk->i])))
		return (ERR_MALLOC);
	if ((errnb = sv_check_path(&ptr, cl)) != IS_OK)
		return (errnb);
	if ((errnb = mkdir(ptr, 0777)) != 0 && !(mk->opt & MKDIR_P))
		mk->opt |= MKDIR_ERR;
	free(ptr);
	if (errnb == 0 && !(mk->opt & MKDIR_P) && (mk->opt & MKDIR_V))
		ptr = "created directory: ";
	else if (errnb != 0 && !(mk->opt & MKDIR_P))
		ptr = "failed to create: ";
	else
		ptr = NULL;
	errnb = IS_OK;
	if (ptr)
		if ((errnb = sv_client_write(mk->cmd[0], cl)) == IS_OK)
			if ((errnb = sv_client_write(": ", cl)) == IS_OK)
				if ((errnb = sv_client_write(ptr, cl)) == IS_OK)
					if ((errnb = sv_client_write(mk->cmd[mk->i], cl)) == IS_OK)
						errnb = sv_client_write("\n", cl);
	return (errnb);
}

int				sv_mkdir(char **cmds, t_client *cl, t_server *sv)
{
	t_mkdir		mk;
	int			errnb;
	char		*dir;

	mk.cmd = cmds;
	if ((errnb = mkdir_opts(cmds, &mk.opt, &mk.i)) != IS_OK)
		return (sv_cmd_err(ft_get_error(errnb), cmds[0], cl, sv));
	while (cmds[mk.i])
	{
		dir = (cmds[mk.i][0] == '/') ? cmds[mk.i] + 1 : cmds[mk.i];
		if (mk.opt & MKDIR_P)
			while (*dir && (dir = ft_strchr(dir, '/')) && *(dir + 1))
			{
				*dir = '\0';
				if ((errnb = mkdir_create(&mk, cl, sv)) != IS_OK)
					return (errnb);
				*dir++ = '/';
			}
		if ((errnb = mkdir_create(&mk, cl, sv)) != IS_OK)
			return (errnb);
		mk.i++;
	}
	if (mk.opt & MKDIR_ERR)
		return (sv_client_write(ERR_OUTPUT, cl));
	return (sv_client_write(OK_OUTPUT, cl));
}
