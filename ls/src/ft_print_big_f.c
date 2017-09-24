/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_big_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 14:38:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/31 22:26:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_print_big_f(t_file *tmp)
{
	if (tmp->type == DT_LNK)
		ft_putchar('@');
	else if (tmp->type == DT_SOCK)
		ft_putchar('=');
	else if (tmp->type == DT_UNKNOWN)
		ft_putchar('%');
	else if (tmp->type == DT_FIFO)
		ft_putchar('|');
	else if (tmp->inf.st_mode & S_IXUSR ||
			 tmp->inf.st_mode & S_IXGRP ||
			 tmp->inf.st_mode & S_IXOTH)
		ft_putchar('*');
	else
		tmp->len--;			
}
