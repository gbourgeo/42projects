/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putend_cl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:59:06 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 11:39:36 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putend_cl(char *str1, char *color1, char *str2, char *color2)
{
	ft_putstr(RESET);
	ft_putstr(color1);
	ft_putstr(str1);
	ft_putstr(RESET);
	ft_putstr(color2);
	ft_putstr(str2);
	ft_putstr(RESET);
}
