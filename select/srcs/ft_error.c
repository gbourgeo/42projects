/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 17:07:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/08 17:09:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_error(const char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
