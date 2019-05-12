/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:57:25 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 11:38:27 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_cl(char *str, char *color)
{
	ft_putstr(RESET);
	ft_putstr(color);
	ft_putstr(str);
	ft_putendl(RESET);
}
