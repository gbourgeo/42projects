/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_stralnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 11:14:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 21:03:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

int				sh_stralnum(const char *str)
{
	size_t		i;

	i = 0;
	if (str)
		while (str[i])
			if (!ft_isalnum(str[i++]))
				return (0);
	return (1);
}
