/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 08:14:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/07 15:07:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void			ft_error(const char *err)
{
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}