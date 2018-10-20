/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:28:45 by root              #+#    #+#             */
/*   Updated: 2018/10/20 15:06:00 by root             ###   ########.fr       */
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
