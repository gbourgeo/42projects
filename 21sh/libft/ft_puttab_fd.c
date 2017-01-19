/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 19:46:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/09 17:02:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_puttable_fd(char **table, int fd)
{
	int			i;

	i = 0;
	while (table && table[i])
	{
		ft_putendl_fd(table[i], fd);
		i++;
	}
}
