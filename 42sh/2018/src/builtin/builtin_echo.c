/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 06:26:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 11:44:37 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "builtin_echo.h"
#include "builtins.h"

static int		echo_error(t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "echo: write error: bad file descriptor\n");
	return (1);
}

static char		builtin_echo_escaped(int c)
{
	static char	table[] = {
		0x07, 0x08, 0x00, 0x00, 0x1B, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x0D, 0x0A, 0x09, 0x00, 0x0B, 0x00, 0x00,
		0x00, 0x00,
	};

	if (c >= 'a' && c <= 'z')
		return (table[c - 'a']);
	return (0);
}

static int		builtin_echo_write(char *arg, int opt)
{
	size_t		i;
	char		c;

	i = 0;
	if (opt & ECHO_OPT_E)
	{
		while ((c = arg[i]))
		{
			if (arg[i] == '\\')
			{
				if (!(c = builtin_echo_escaped(arg[i + 1])))
					c = '\\';
				else
					i++;
			}
			if (ft_dprintf(STDOUT_FILENO, "%c", c) < 0)
				return (1);
			i++;
		}
	}
	else if (ft_dprintf(STDOUT_FILENO, "%s", arg) < 0)
		return (1);
	return (0);
}

static int		builtin_echo_option(char *arg, int *opt)
{
	int			i;

	i = 0;
	while (arg[++i])
		if (arg[i] == 'n')
			*opt |= ECHO_OPT_N;
		else if (arg[i] == 'e')
			*opt |= ECHO_OPT_E;
		else
			return (1);
	return (0);
}

int				builtin_echo(t_execute *exec, t_s_env *e)
{
	int			i;
	int			opt;

	i = 1;
	opt = 0;
	while (exec->cmd[i] && exec->cmd[i][0] == '-' && exec->cmd[i][1])
		if (builtin_echo_option(exec->cmd[i], &opt))
			break ;
		else
			i++;
	while (exec->cmd[i])
		if (builtin_echo_write(exec->cmd[i], opt)
		|| (exec->cmd[i + 1] && ft_dprintf(STDOUT_FILENO, " ") < 0))
			return (echo_error(e));
		else
			i++;
	if (!(opt & ECHO_OPT_N) && ft_dprintf(STDOUT_FILENO, "\n") < 0)
		return (echo_error(e));
	return (0);
}
