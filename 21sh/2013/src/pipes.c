/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:25:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 14:47:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			pipes_check(char **args, t_env *e)
{
	long		i;
	long		nb;

	i = 0;
	nb = 0;
	while (args[i])
	{
		if (*args[i] == '|' || *args[i] == '>' || *args[i] == '<')
			nb++;
		i++;
	}
	if (nb > 0)
		e->ret = pipes_prepare(args, e, nb);
	else
		check_and_exec(args, e);
}
