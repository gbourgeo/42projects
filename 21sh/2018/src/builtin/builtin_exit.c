/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:42:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 20:16:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "builtins.h"

static int		str_full_digit(const char *s)
{
	size_t		i;

	i = 0;
	if (*s == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

static int		exit_error(int err, const char *cmdname, t_s_env *e)
{
	static char	*errors[] = {
		"too many arguments", "numeric argument required",
	};

	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->interactive)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->interactive);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", cmdname, errors[err]);
	e->shell_loop = !err;
	return (err + 1);
}

int				builtin_exit(t_execute *exec, t_s_env *e)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	e->shell_loop = 0;
	if (exec->cmd[1])
	{
		if (exec->cmd[2])
			return (exit_error(0, exec->cmd[0], e));
		else if (!str_full_digit(exec->cmd[1]))
			return (exit_error(1, exec->cmd[0], e));
		*e->ret = (unsigned char)ft_atoi(exec->cmd[1]);
	}
	return (*e->ret);
}
