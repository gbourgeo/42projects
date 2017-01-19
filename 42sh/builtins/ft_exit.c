/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 12:41:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 18:41:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		free_and_exit(char **args, t_env *e)
{
	ft_putendl("exit");
	ft_term_restore(e);
	if (args)
		ft_free(&args);
	if (e->history)
		ft_free_history(e->history);
	if (e->env)
		ft_free(&e->env);
	if (e->path)
		free(e->path);
	if (e->term)
		free(e->term);
	close(e->fd);
	exit(e->status);
}

void			ft_exit(char **args, t_env *e)
{
	int			i;

	i = 0;
	if (!args || !args[0] || !args[1])
		free_and_exit(args, e);
	if (!args[2])
	{
		while (args[1][i] != '\0')
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_putendl("42sh: exit: Non numeric value detected.");
				e->status = 255;
				free_and_exit(args, e);
			}
			i++;
		}
		e->status = ft_atoi(args[1]);
		free_and_exit(args, e);
	}
	ft_putendl("42sh: exit: too many arguments.");
	e->status = 1;
}
