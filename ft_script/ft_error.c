/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 01:40:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/24 03:21:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				ft_error(int aff_file, char *mess, t_env *e)
{
	ft_putstr_fd(e->prog, 2);
	ft_putstr_fd(": Error: ", 2);
	ft_putstr_fd(mess, 2);
	if (aff_file)
	{
		ft_putstr_fd(e->file, 2);
		ft_putendl_fd(".", 2);
	}
	return (1);
}
