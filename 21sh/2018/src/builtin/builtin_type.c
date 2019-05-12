/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:52:23 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/22 12:17:12 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_type.h"
#include "builtin_alias.h"
#include "shell_lib.h"

/*
**	type [-afptP] name [name ...]
**
**	Options:
**
**	-a	display all locations containing an executable named NAME;
**		includes aliases, builtins, and functions, if and only if
**		the `-p' option is not also used
**
**	-f	suppress shell function lookup
**
**	-P	force a PATH search for each NAME, even if it is an alias,
**		builtin, or function, and returns the name of the disk file
**		that would be executed
**
**	-p	returns either the name of the disk file that would be executed,
**		or nothing if `type -t NAME' would not return `file'
**
**	-t	output a single word which is one of `alias', `keyword',
**		`function', `builtin', `file' or `', if NAME is an alias,
**		shell reserved word, shell function, shell builtin, disk file,
**		or not found, respectively
*/

int		builtin_type(t_execute *exec, t_s_env *e)
{
	t_type		*type;
	int			i;
	int			ret;

	i = 0;
	ret = 1;
	type = def_s_type(exec);
	while (++i <= type->cnt_opt)
	{
		if (illegal_option(exec->cmd[i]))
		{
			free(type);
			return (2);
		}
		get_option(exec->cmd[i], type, 0);
	}
	if (exec->cmd[i--])
	{
		while (exec->cmd[++i])
			ret *= exec_type(exec->cmd[i], type, e);
		free(type);
		return (ret);
	}
	free(type);
	return (0);
}

int		exec_type(char *arg, t_type *type, t_s_env *e)
{
	int		ret;
	char	**paths;

	ret = 1;
	if (!(ret *= is_alias(arg, e, type)))
	{
		if ((!type->opt_p && !type->opt_bigp && !type->opt_a) && !type->opt)
			return (0);
	}
	if ((!(ret *= is_builtin(arg, type)) && !type->opt_a) && !type->opt)
		return (0);
	if ((!(ret *= is_keyword(arg, type)) && !type->opt_a) && !type->opt)
		return (0);
	paths = ft_strsplit(sh_getnenv("PATH", e->public_env), ':');
	if (!(ret *= is_file(arg, paths, type, ret)))
	{
		sh_freetab(&paths);
		return (0);
	}
	ft_dprintf(2, "42sh: type: %s: not found\n", arg);
	sh_freetab(&paths);
	return (ret);
}
