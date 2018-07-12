/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 13:02:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/07/12 08:09:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		check(char **command, t_opt *opt)
{
	int			i;

	if ((i = ft_env_check_opt(command, opt, 0, 0)) == -1)
		return (-1);
	if ((i = ft_env_check_opt_plus(command, opt, i)) == -1)
		return (-1);
	if (opt->u && ft_opt_u(opt, -1, -1) == -1)
		return (-1);
	if (opt->i)
		ft_opt_i(opt);
	if (opt->extra)
		ft_opt_extra(opt);
	if (opt->p && ft_opt_p(opt, &command[i]) == -1)
		return (-1);
	return (i);
}

int				ft_env(char **command, t_env *e)
{
	t_opt		opt;
	int			i;

	ft_memset(&opt, 0, sizeof(opt));
	if ((opt.cpy = ft_tabdup(e->env)) == NULL)
		return (ft_enverror("malloc failed", 0, &opt));
	if (!command[1])
		ft_puttab(e->env);
	else
	{
		if ((i = check(command, &opt)) < 0)
			return (1);
		if (command[i])
			e->ret = check_and_exec(&command[i], opt.cpy, e);
		else
			ft_puttab(opt.cpy);
	}
	ft_freetab(&opt.cpy);
	ft_freestr(&opt.path);
	ft_freestr(&opt.cmd);
	ft_freetab(&opt.ptr);
	free(opt.extra);
	return (e->ret);
}

int				ft_enverror(char *err, char c, t_opt *opt)
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
	ft_freetab(&opt->cpy);
	ft_freestr(&opt->path);
	ft_freestr(&opt->cmd);
	ft_freetab(&opt->ptr);
	ft_freetab(&opt->extra);
	return (-1);
}
