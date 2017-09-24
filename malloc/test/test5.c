/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/09/24 07:08:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_malloc.h"

void	ft_putstr(char const *str)
{
	while (*str)
		write(1, str++, 1);
}

int		main(void)
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	ft_putstr("\n---------show_alloc_mem()------------\n");
	show_alloc_mem();
	ft_putstr("\n---------show_alloc_mem_ex()---------\n");
//	show_alloc_mem_ex();
	return (0);
}
