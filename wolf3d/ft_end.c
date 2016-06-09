/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 12:45:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/04/25 12:48:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_end(char *str, t_env *e, int status)
{
	if (status == EXIT_FAILURE)
		ft_putendl_fd(str, 2);
	else
		ft_putendl_fd(str, 1);
	ft_free_all(e);
	exit(status);
}
