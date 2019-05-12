/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 17:07:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/05 15:32:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_error(const char *str, t_env *e)
{
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	e->status = 1;
	ft_exit(NULL, e);
}
