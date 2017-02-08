/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 12:41:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/06 21:23:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		free_and_exit(char **args)
{
	update_history();
	ft_free(&data.env);
	ft_free(&data.path);
	ft_free_hist(&data.hist);
	ft_free(&args);
	if (data.histpath)
		free(data.histpath);
	if (data.cpy.str)
		free(data.cpy.str);
	restore_term();
	ft_bzero(&data, sizeof(data));
	ft_putendl_fd("exit", data.fd);
	exit(data.ret);
}

int				ft_exit(char **args, char ***env)
{
	(void)env;
	if (!args || !args[1])
		free_and_exit(args);
	if (args[2])
		ft_putendl_fd("exit: Too many arguments.", 2);
	else
	{
		data.ret = ft_atoi(args[1]);
		free_and_exit(args);
	}
	return (-1);
}
