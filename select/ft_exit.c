/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 23:01:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/12 23:01:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_exit(int status)
{
	t_info	*info;

	info = tgetinfo();
	ft_term_restore(status);
	close(info->fd);
	exit(EXIT_FAILURE);
}
