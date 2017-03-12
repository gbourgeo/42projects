/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:48:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 14:48:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				pipes_error(char *str, char **args, long *nb, t_pipe *pi)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	if (!ft_strncmp(str, "parse", 5))
		ft_putchar_fd('\n', 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(args[nb[0] + 1], 2);
	}
	pipes_free(args, nb[1], pi);
	return (1);
}
