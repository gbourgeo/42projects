/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:46:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/11 18:48:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int			ft_usage(char *progname)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(progname, 2);
	ft_putstr_fd(USAGE_ARGS, 2);
	return (EXIT_FAILURE);
}

static int			ft_flags_error(char *av, int j, t_env *env)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(env->prog_name, 2);
	if (av == NULL)
		ft_putendl_fd(": at least one file must be specified", 2);
	else if (env->options[opt_none] == 0 && j == 0)
	{
		ft_putstr_fd(": one of -", 2);
		ft_putstr_fd(OPTIONS, 2);
		ft_putendl_fd(" must be specified", 2);
	}
	else
	{
		ft_putstr_fd(": unknown char `", 2);
		ft_putchar_fd(av[j], 2);
		ft_putstr_fd("' in flag ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\n\n", 2);
	}
	free(env->options);
	return (-1);
}

static int			ft_flags_plus(int i, char **av, t_env *env)
{
	int				j;
	char			*tmp;

	j = 1;
	while (av[i][j] != '\0')
	{
		tmp = ft_strchr(OPTIONS, av[i][j]);
		if (tmp == NULL)
			return (ft_flags_error(av[i], j, env));
		env->options[ft_strlen(OPTIONS) - ft_strlen(tmp)] = 1;
		env->options[opt_none] = 1;
		j++;
	}
	return (0);
}

static int			ft_check_flags(char **av, t_env *env)
{
	int				i;

	if (!av[1])
		return (-1);
	env->options = malloc(sizeof(*env->options) * (ft_strlen(OPTIONS) + 1));
	if (env->options == NULL)
		return (-1);
	ft_memset(env->options, '\0', ft_strlen(OPTIONS) + 1);
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_flags_plus(i, av, env) == -1)
			return (-1);
		i++;
	}
	if (av[i] == NULL || env->options[opt_none] == 0)
		return (ft_flags_error(av[i], 0, env));
	return (i);
}

int					main(int ac, char **av)
{
	t_env			env;
	size_t			errors;

	errors = 0;
	env.prog_name = av[0];
	ac = ft_check_flags(av, &env);
	if (ac == -1)
		return (ft_usage(av[0]));
	while (av[ac])
	{
		env.file_name = av[ac];
		env.file_type = NONE;
		errors += ft_openfile(&env);
		ac++;
	}
	free(env.options);
	if (errors)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
