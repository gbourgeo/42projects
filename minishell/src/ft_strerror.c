/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 18:06:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/05 15:09:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strerror(char *str)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_freestr(&str);
	}
	ft_putchar_fd('\n', 2);
}
