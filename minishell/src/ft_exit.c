/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 12:41:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 16:17:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		free_and_exit(char **args, t_env *e)
{
	ft_freetab(&e->env);
	ft_freetab(&e->path);
	ft_freestr(&e->command);
	ft_freetab(&args);
	ft_putendl("exit");
	exit(e->ret);
}

int				ft_exit(char **args, t_env *e)
{
	if (!args || !args[1])
		free_and_exit(args, e);
	if (args[2])
		ft_putendl_fd("exit: Too many arguments.", 2);
	else
	{
		e->ret = ft_atoi(args[1]);
		free_and_exit(args, e);
	}
	return (-1);
}
