/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:22:25 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/28 20:23:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"
#include "builtin_type.h"
#include "put.h"
#include "shell.h"

/*
**	export name[=word]...
**
** 	When -p is specified, export shall write to the standard output the names
**  and values of all exported variables, in the following format:
**
**	"export %s=%s\n", <name>, <value>
**	export -p
**
**	Mark each name to be passed to child processes in the environment.
**	The names refer to shell variables. If no names are supplied, or if the
**	-p option is given, a list of names of all exported variables is displayed.
**	The -p option displays output in a form that may be reused as input. If a
**	variable name is followed by =value, the value of the variable is set to
**	value.
**
**	The return status is zero unless an invalid option is supplied, one of the
**	names is not a valid shell variable name.
*/

void		get_tree_env(void)
{
	t_line	*line;

	line = get_struct();
	free_tree(GET_TREE(line->tree, ENV));
	GET_TREE(line->tree, ENV) = NULL;
	if (line->public_env && *line->public_env)
		fill_tree_env(*line->public_env, &GET_TREE(line->tree, ENV));
	if (line->private_env && *line->private_env)
		fill_tree_env(*line->private_env, &GET_TREE(line->tree, ENV));
	if (GET_TREE(line->tree, ENV))
		set_psblty(GET_TREE(line->tree, ENV), 1);
}

int			builtin_export(t_execute *exec, t_s_env *e)
{
	int			i;
	int			ret;
	t_export	*export;

	export = def_s_export(exec);
	i = 0;
	ret = 0;
	while (++i <= export->cnt_opt && ret == 0)
	{
		ft_strchr(exec->cmd[i], 'p') ? export->opt_p = 1 : 0;
		if (illegal_option_export(exec->cmd[i]))
			ret = 2;
	}
	if (exec->cmd[i--] && ret != 2)
	{
		while (exec->cmd[++i])
			ret += exec_export(exec->cmd[i], e);
		get_tree_env();
		free(export);
		return ((ret > 0) ? 1 : 0);
	}
	if (ret != 2)
		export_print(e->exported_env, e->public_env);
	free(export);
	return (ret);
}

t_export	*def_s_export(t_execute *exec)
{
	t_export	*export;

	export = ft_memalloc(sizeof(t_export));
	export->opt_p = 0;
	export->cnt_opt = count_options(exec->cmd);
	return (export);
}
