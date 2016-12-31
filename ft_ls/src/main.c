/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 17:42:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/31 19:22:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			ft_exceptions(char c, t_opt *options)
{
	if (c == 'p')
		options->big_f = 0;
	else if (c == 'F')
		options->p = 0;
	else if (c == 'u')
		options->date = 0;
	else if (c == 'c')
		options->date = 2;
	else if (c == 'U')
		options->date = 3;
	else if (c == '1')
	{
		options->l = 0;
		options->g = 0;
		options->o = 0;
	}
}

static void			ft_check_arguments(char *av, t_opt *options)
{
	char			args[] = LS_OPTIONS;
	int				i;
	int				j;

	j = 1;
	while (av[j])
	{
		if (!ft_strchr(LS_OPTIONS, av[j]))
			ft_exit(av[j]);
		i = 0;
		while (args[i])
		{
			if (args[i] == av[j])
				*((char*)options + i * sizeof(char)) = 1;
			i++;
		}
		ft_exceptions(av[j], options);
		j++;
	}
}

static void			ft_sort_file(int i, char **av)
{
	int				j;
	char			*tmp;

	while (av[i])
	{
		j = i + 1;
		while (av[j])
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
			}
			j++;
		}
		if (av[i][0] == '\0')
			ft_exit(0);
		i++;
	}
}

static int			ft_get_arguments(int *ac, char **av, t_opt *opt)
{
	int				i;

	i = 1;
	while (av[i])
	{
		*ac -= 1;
		if (!ft_strcmp(av[i], "--"))
		{
			i++;
			*ac -= 1;
			break ;
		}
		if (av[i][0] == '-' && av[i][1])
			ft_check_arguments(av[i], opt);
		else
			break ;
		i++;
	}
	if (!av[i])
		return (ft_get_dir(".", opt));
	if (!opt->big_s && !opt->f)
		ft_sort_file(i, av);
	while (av[i])
		opt->ret = ft_get_dir(av[i++], opt);
	return (opt->ret);
}

int					main(int ac, char **av)
{
	t_opt			options;

	ioctl(0, TIOCGWINSZ, &options.sz);
	ft_clear_opt(&options);
	options.ret = ft_get_arguments(&ac, av, &options);
	if (!options.f)
		ft_sort(&options);
	if (options.files.file)
		ft_print_files(&options.files, &options);
	if (options.dir)
		ft_print_dir(ac, &options);
	ft_clear_opt_files(&options.files.file, options.l);
	ft_clear_dir_files(&options.dir, options.l);
	return (options.ret);
}
