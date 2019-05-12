/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:51:34 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 11:39:16 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_cl(char *str, char *color)
{
	ft_putstr(RESET);
	ft_putstr(color);
	ft_putstr(str);
	return (ft_putstr(RESET));
}
