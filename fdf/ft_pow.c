/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 09:37:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/02/19 09:37:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				ft_pow(int nb, int power)
{
	if (power <= 0)
		return (1);
	if (power == 1)
		return (nb);
	nb *= ft_pow(nb, power - 1);
	return (nb);
}
