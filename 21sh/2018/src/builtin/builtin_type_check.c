/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 18:59:02 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/29 20:57:54 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_type.h"
#include "shell_lib.h"
#include "builtin_alias.h"

int		is_builtin(char *arg, t_type *type)
{
	if (ft_strcmp(arg, "cd") == 0 || ft_strcmp(arg, "echo") == 0
			|| ft_strcmp(arg, "env") == 0 || ft_strcmp(arg, "exit") == 0
			|| ft_strcmp(arg, "setenv") == 0 || ft_strcmp(arg, "unalias") == 0
			|| ft_strcmp(arg, "unsetenv") == 0 || ft_strcmp(arg, "type") == 0
			|| ft_strcmp(arg, "alias") == 0 || ft_strcmp(arg, "set") == 0
			|| ft_strcmp(arg, "unset") == 0 || ft_strcmp(arg, "export") == 0)
	{
		if (type->opt_p || type->opt_bigp)
			return (0);
		if (type->opt_t)
			ft_printf("builtin\n");
		else
			ft_printf("%s is a shell builtin\n", arg);
		return (0);
	}
	return (1);
}

int		is_alias(char *arg, t_s_env *e, t_type *type)
{
	t_alias		*alias;

	alias = e->alias_list;
	while (alias)
	{
		if (ft_strcmp(arg, alias->key) == 0)
		{
			if (type->opt_p || type->opt_bigp)
				return (0);
			if (type->opt_t)
				ft_printf("alias\n");
			else
				ft_printf("%s is aliased to `%s'\n", arg, alias->value);
			return (0);
		}
		alias = alias->next;
	}
	return (1);
}

int		is_keyword(char *arg, t_type *type)
{
	if (ft_strcmp(arg, "!") == 0 || ft_strcmp(arg, "[") == 0
		|| ft_strcmp(arg, "]") == 0 || ft_strcmp(arg, "{") == 0
		|| ft_strcmp(arg, "}") == 0)
	{
		if (type->opt_p || type->opt_bigp)
			return (0);
		if (type->opt_t)
			ft_printf("keyword\n");
		else
			ft_printf("%s is a shell keyword\n", arg);
		return (0);
	}
	return (1);
}

int		is_file(char *arg, char **paths, t_type *type, int ret)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	while (paths && paths[++i])
	{
		tmp1 = ft_strjoin(paths[i], "/");
		tmp2 = ft_strjoinfree(tmp1, arg, 1);
		if (lstat(tmp2, &st) == 0 && (S_IFREG & st.st_mode))
		{
			if (!is_file_2(type, ret, &tmp2, arg))
				return (0);
			if (!type->opt_a || (type->opt_a && paths[i + 1] != NULL))
			{
				free(tmp2);
				return (0);
			}
		}
		else
			free(tmp2);
	}
	return (1);
}

int		is_file_2(t_type *type, int ret, char **tmp2, char *arg)
{
	if (type->opt_p && !ret)
	{
		ft_strdel(tmp2);
		return (0);
	}
	if (type->opt_bigp || type->opt_p)
		ft_printf("%s\n", *tmp2);
	else if (type->opt_t)
		ft_printf("file\n");
	else
		ft_printf("%s is %s\n", arg, *tmp2);
	return (1);
}
