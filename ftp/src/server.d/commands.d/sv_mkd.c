/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mkd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:40:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:53:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sv_main.h"
#include "sv_struct.h"

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

static int		mkdir_create(t_mkdir *mk, t_client *cl)
{
	char		*dir;
	int			errnb;

	if (!(dir = ft_strdup(mk->cmd[mk->i])))
		return (ERR_MALLOC);
	if ((errnb = sv_check_path(&dir, cl)) != IS_OK)
		return (errnb);
	if ((errnb = mkdir(dir, 0777)) != 0 && !(mk->opt & MKDIR_P))
		mk->opt |= MKDIR_ERR;
	errnb = IS_OK;
	if (errnb == 0 && !(mk->opt & MKDIR_P) && (mk->opt & MKDIR_V))
		errnb = sv_response(cl, "257 \"%s\" directory created", dir);
	else if (errnb != 0 && !(mk->opt & MKDIR_P))
		errnb = sv_response(cl, "550 failed to create %s", dir);
	free(dir);
	return (errnb);
}

/*
** MKD
** 257
** 500, 501, 502, 421, 530, 550
*/

int				sv_mkd(char **cmds, t_client *cl)
{
	t_mkdir		mk;
	int			errnb;
	char		*dir;

	mk.cmd = cmds;
	if ((errnb = mkdir_opts(cmds, &mk.opt, &mk.i)) != IS_OK)
		return (sv_response(cl, "501 %s", ft_get_error(errnb)));
	while (cmds[mk.i])
	{
		dir = (cmds[mk.i][0] == '/') ? cmds[mk.i] + 1 : cmds[mk.i];
		if (mk.opt & MKDIR_P)
			while (*dir && (dir = ft_strchr(dir, '/')) && *(dir + 1))
			{
				*dir = '\0';
				if ((errnb = mkdir_create(&mk, cl)) != IS_OK)
					return (errnb);
				*dir++ = '/';
			}
		if ((errnb = mkdir_create(&mk, cl)) != IS_OK)
			return (errnb);
		mk.i++;
	}
	return (errnb);
}

/*
** MKD <SP> <chemin d'accès> <CRLF>
*/

int				sv_mkd_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the directory specified in the pathname",
		"to be created as a directory (if the pathname is absolute)",
		"or as a subdirectory of the current working directory (if",
		"the pathname is relative).",
		"Options are:",
		"	-p		Create parent directories without error if they exist",
		"	-v		Print a message for each directory created", NULL
	};

	return (sv_print_help(cl, cmd, "[-vp] <pathname>", help));
}
