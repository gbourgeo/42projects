/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_cl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:56:12 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 11:39:30 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_cl(int nb, char *color)
{
	ft_putstr(RESET);
	ft_putstr(color);
	ft_putnbr(nb);
	ft_putstr(RESET);
}
