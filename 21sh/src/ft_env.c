/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 13:02:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 04:01:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		check(char **command, t_opt *opt)
{
	int			i;

	if ((i = ft_env_check_opt(command, opt, 1, 0)) == -1)
		return (-1);
	if ((i = ft_env_check_opt_plus(command, opt, i)) == -1)
		return (-1);
	if (opt->u && ft_env_u(opt) == -1)
		return (-1);
	if (opt->i)
		ft_env_i(opt);
	if (opt->extra)
		ft_env_extra(opt);
	if (opt->p && ft_env_p(opt, &command[i]) == -1)
		return (-1);
	return (i);
}

static void		free_opt(t_opt *opt)
{
	ft_free(&opt->env);
	if (opt->path)
		free(opt->path);
	if (opt->cmd)
		free(opt->cmd);
	ft_free(&opt->ptr);
	free(opt->extra);
}

static void		ft_error(char *err, t_opt *opt, t_env *e)
{
	e->ret = 1;
	if (err)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(err, 2);
		ft_putchar_fd('\n', 2);
	}
	free_opt(opt);
}

void			ft_env(char **command, t_env *e)
{
	t_opt		opt;
	char		**tmp;
	int			i;

	ft_memset(&opt, 0, sizeof(opt));
	e->ret = 0;
	if ((opt.env = ft_tabdup(e->env)) == NULL)
		return (ft_error("malloc failed", &opt, e));
	if (!command[1])
		ft_puttab(opt.env);
	else
	{
		if ((i = check(command, &opt)) < 0)
			return (ft_error(NULL, &opt, e));
		if (command[i])
		{
			tmp = e->env;
			e->env = opt.env;
			check_and_exec(&command[i], e);
			e->env = tmp;
		}
		else
			ft_puttab(opt.env);
	}
	free_opt(&opt);
}

int				ft_env_error(char *err, char c)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(err, 2);
	if (c)
	{
		ft_putstr_fd(" -- ", 2);
		ft_putchar_fd(c, 2);
		write(2, "\nusage: env [-iv] [-P utilpath] [-S string] [-u name]", 53);
		write(2, "\n           [name=value ...] [utility [argument ...]]", 53);
	}
	ft_putchar_fd('\n', 2);
	return (-1);
}

void			ft_update_env(char *path, char **args, t_env *e)
{
	char		*tmp;
	size_t		i;

	i = 0;
	if (path)
	{
		tmp = args[0];
		args[0] = path;
		path = tmp;
	}
	while (e->env && e->env[i])
	{
		if (ft_strncmp(e->env[i], "_=", 2) == 0)
		{
			free(e->env[i]);
			e->env[i] = ft_strjoin("_=", args[ft_tablen(args) - 1]);
			break ;
		}
		i++;
	}
	if (path)
		free(path);
}
