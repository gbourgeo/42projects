/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_validnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:05:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 15:08:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_validnumber(char **s, int ssize)
{
	int		i;
	int		j;

	i = 0;
	while (i < ssize)
	{
		j = 0;
		while (s[i][j])
			if (!ft_isdigit(s[i][j++]))
				return (0);
		if (ft_atoi(s[i]) < 0 || ft_atoi(s[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}
