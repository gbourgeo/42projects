/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:06:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 16:08:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strisalnum(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str) && !ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
