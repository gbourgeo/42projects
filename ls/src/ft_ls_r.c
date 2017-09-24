/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 11:15:43 by gilles            #+#    #+#             */
/*   Updated: 2014/12/21 13:13:20 by gilles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_ls_r(t_dir *dir, int a)
{
	t_file		*tmp;

	tmp = dir->file;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (a)
			ft_putendl(tmp->name);
		else if (*(tmp->name) != '.')
			ft_putendl(tmp->name);
		tmp = tmp->prev;
	}
}
