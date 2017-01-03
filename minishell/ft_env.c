/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 13:02:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/03 23:42:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	ft_free(&opt->cpy);
	ft_free(&opt->ptr);
	ft_free(&opt->extra);
	return (-1);
}

static char		**ft_fill_opt_u(char **cmd, int *i, int j, t_opt *opt)
{
	char		**tab;
	int			k;

	if ((tab = (char **)malloc(ft_tablen(opt->ptr) + 2)) == NULL)
		return (opt->ptr);
	k = 0;
	while (opt->ptr && opt->ptr[k])
	{
		tab[k] = opt->ptr[k];
		k++;
	}
	tab[k] = (cmd[*i][j] == '\0') ? cmd[++(*i)] : &cmd[*i][j];
	tab[k + 1] = NULL;
	opt->u = 1;
	free(opt->ptr);
	return (tab);
}

static int		ft_check_opt(char **cmd, t_opt *opt, int i, int j)
{
	while (cmd[++i] && cmd[i][0] == '-')
	{
		if (!cmd[i][1])
			opt->i = 1;
		if (!ft_strcmp(cmd[i], "--"))
			return (i);
		j = 0;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '-' || cmd[i][j] == 'i')
				opt->i = 1;
			else if (cmd[i][j] == 'v')
				opt->v = 1;
			else if (cmd[i][j] == 'u')
			{
				if ((opt->ptr = ft_fill_opt_u(cmd, &i, j + 1, opt)) == NULL)
					return (ft_enverror("malloc failed", 0, opt));
				break ;
			}
			else
				return (ft_enverror("illegal option", cmd[i][j], opt));
		}
	}
	return (i);
}

static int		ft_check_opt_plus(char **cmd, t_opt *opt, int i)
{
	char		**tab;
	int			k;

	while (ft_strchr(cmd[i], '='))
	{
		if ((tab = (char **)malloc(ft_tablen(opt->extra) + 2)) == NULL)
			return (ft_enverror("malloc failed", 0, opt));
		k = 0;
		while (opt->extra && opt->extra[k])
		{
			tab[k] = opt->extra[k];
			k++;
		}
		tab[k] = cmd[i];
		tab[k + 1] = NULL;
		free(opt->extra);
		opt->extra = tab;
		i++;
	}
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
		if ((i = ft_check_opt(command, &opt, 0, 0)) == -1)
			return (1);
		if ((i = ft_check_opt_plus(command, &opt, i)) == -1)
			return (1);
		if (opt.u && ft_opt_u(&opt) == -1)
			return (1);
		if (opt.i)
			ft_opt_i(&opt);
		if (opt.extra)
			ft_opt_extra(&opt);
		if (command[i])
			e->ret = fork_function(&command[i], opt.cpy);
		else
			ft_puttab(opt.cpy);		
	}
	ft_free(&opt.cpy);
	ft_free(&opt.ptr);
	ft_free(&opt.extra);
	return (e->ret);
}
