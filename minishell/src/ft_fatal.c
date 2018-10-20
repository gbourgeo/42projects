/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:07:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 21:07:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_fatal(const char *error, t_env *e)
{
	ft_putendl_fd(error, STDERR_FILENO);
	ft_freetab(&e->env);
	ft_freetab(&e->path);
	ft_freestr(&e->command);
	exit(EXIT_FAILURE);
}
