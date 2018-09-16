/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 18:25:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/12 15:29:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		second_check(char *buf, t_args *tmp);
static void		third_check(char *buf, t_args *tmp, int lst_col);
static void		fourth_check(char *buf, t_args *tmp, int lst_col);
static void		last_check(t_args *tmp);

void			key_check(char *buf, t_info *info)
{
	t_args	*tmp;

	tmp = info->elems;
	while (tmp->current != 1)
		tmp = tmp->next;
	if (buf[0] == 10)
		ft_retur(info);
	else if (buf[0] == 27 && buf[1] != 91)
		ft_exit(0);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
		ft_del_elem(tmp, info);
	else if (buf[0] == 127)
		ft_del_elem(tmp, info);
	else if (buf[0] == 27 && buf[1] == 91)
	{
		second_check(buf, tmp);
		third_check(buf, tmp, info->lst_col);
		fourth_check(buf, tmp, info->lst_col);
	}
	else if (buf[0] == 32 && buf[1] == 0)
		last_check(tmp);
}

static void		second_check(char *buf, t_args *tmp)
{
	if  (buf[2] == 65)
	{
		tmp->current = 0;
		tmp->prev->current = 1;
		return ;
	}
	if (buf[2] == 66)
	{
		tmp->current = 0;
		tmp->next->current = 1;
		return ;
	}
}

static void		third_check(char *buf, t_args *tmp, int lst_col)
{
	t_args	*tmp2;

	tmp2 = tmp;
	if (buf[2] == 67)
	{
		while ((tmp = tmp->next) != tmp2)
		{
			if ((tmp->x == (tmp2->x + lst_col + 1)) && tmp->y == tmp2->y)
			{
				tmp2->current = 0;
				tmp->current = 1;
				return ;
			}
		}
		return ;
	}
}

static void		fourth_check(char *buf, t_args *tmp, int lst_col)
{
	t_args	*tmp2;

	tmp2 = tmp;
	if (buf[2] == 68 && tmp2->x != 0)
	{
		while ((tmp = tmp->prev) != tmp2)
		{
			if ((tmp->x == (tmp2->x - lst_col - 1)) && tmp->y == tmp2->y)
			{
				tmp2->current = 0;
				tmp->current = 1;
				return ;
			}
		}
	}
}

static void		last_check(t_args *tmp)
{
	if (tmp->selected == 0)
	{
		tmp->current = 0;
		tmp->next->current = 1;
		tmp->selected = 1;
	}
	else
	{
		tmp->current = 0;
		tmp->next->current = 1;
		tmp->selected = 0;
	}
}
