/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:01:54 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/29 13:11:16 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"
#include "builtin_set.h"
#include "builtin_unset.h"

int		builtin_set(t_execute *exec, t_s_env *e)
{
	int		i;
	char	**clone;

	if (!exec->cmd[1])
	{
		clone = clone_2_arr(e->private_env, e->public_env);
		export_sort(&clone);
		i = -1;
		while (clone[++i])
			print_set(clone[i]);
		sh_freetab(&clone);
	}
	return (0);
}

void	print_set(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\t')
			ft_putstr("\\t");
		else if (s[i] == '\n')
			ft_putstr("\\n");
		else
			ft_putchar(s[i]);
		i++;
	}
	ft_putstr("\n");
}

void	exec_unset(char *arg, t_s_env *e)
{
	exec_unset_check(arg, e);
}
