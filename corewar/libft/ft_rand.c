/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 05:06:42 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/10 14:13:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <inttypes.h>
#endif
#include "libft.h"

int			ft_rand(int min, int max, void *random)
{
	uintptr_t	n;
	uintptr_t	rand;

	rand = (uintptr_t)random;
	n = (uintptr_t)random;
	while (n >= 10)
	{
		rand += (n % 10);
		n /= 10;
	}
	rand = (rand % (max - min + 1)) + min;
	return (rand);
}
