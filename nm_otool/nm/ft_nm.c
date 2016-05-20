/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/15 04:31:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 03:23:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int			ft_options_error(char invalid, t_base *env)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(env->prog_name, 2);
	ft_putstr_fd(" invalid argument -", 2);
	ft_putchar_fd(invalid, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(env->prog_name, 2);
	ft_putstr_fd(" [", 2);
	ft_putstr_fd(OPTIONS, 2);
	ft_putstr_fd("] [file ...]\n", 2);
	ft_putendl_fd(USAGE_ARGS, 2);
	free(env->options);
	return (-1);
}

static int			ft_options_plus(char *av, t_base *env)
{
	int				i;
	char			*tmp;

	i = 1;
	while (av[i] != '\0')
	{
		if ((tmp = ft_strchr(OPTIONS, av[i])) == NULL ||
			(*tmp == '-' && (i != 1 || av[i + 1])))
			return (ft_options_error(av[i], env));
		env->options[ft_strlen(OPTIONS) - ft_strlen(tmp)] = 1;
		env->options[opt_none] = 1;
		i++;
	}
	return (0);
}

static int			ft_options(char **av, t_base *env)
{
	int				i;

	i = 1;
	env->options = malloc(ft_strlen(OPTIONS) * sizeof(*env->options));
	if (env->options == NULL)
		return (-1);
	ft_memset(env->options, '\0', ft_strlen(OPTIONS));
	while (av[i] != '\0' && av[i][0] == '-')
	{
		if (ft_options_plus(av[i], env) == -1)
			return (-1);
		i++;
		if (env->options[0] || !av[i - 1][1])
			break ;
	}
	return (i);
}

int					main(int ac, char **av)
{
	t_base			env;
	int				i;
	int				errors;

	errors = 0;
	env.prog_name = av[0];
	if ((i = ft_options(av, &env)) == -1)
		return (EXIT_FAILURE);
	env.nb_files = ac - i;
	env.file_name = (av[i] == '\0') ? "a.out" : av[i];
	while (env.file_name)
	{
		env.file_type = NONE;
		errors = ft_do_nm(&env);
		if (av[i] == '\0')
			break ;
		i++;
		env.file_name = av[i];
	}
	free(env.options);
	return (errors);
}
