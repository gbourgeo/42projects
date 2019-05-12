/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 04:49:05 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/14 04:49:56 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrstr_fd(char **str, char c, int fd)
{
	while (*str)
	{
		ft_putstr_fd(*str++, fd);
		if (*str)
			ft_putchar_fd(c, fd);
	}
}
