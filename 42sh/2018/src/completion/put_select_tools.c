/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_select_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:00:36 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/15 20:21:45 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

void	get_isput(t_slct *select, int len, int lvl, int *tres)
{
	if (select->next)
		get_isput(select->next, len, lvl, tres);
	if (select->down)
		get_isput(select->down, len, lvl + 1, tres);
	else if (lvl == len)
		get_put(select->mln->tern_next, tres, select->mln->value);
}

void	reset_isput(t_slct *select, int len, int lvl)
{
	if (select->next)
		reset_isput(select->next, len, lvl);
	if (select->down)
		reset_isput(select->down, len, lvl + 1);
	else if (lvl == len)
		reset_put(select->mln->tern_next);
}

void	get_psb(t_slct *select, int len, int lvl, int *psb)
{
	if (select->next)
		get_psb(select->next, len, lvl, psb);
	if (select->down)
		get_psb(select->down, len, lvl + 1, psb);
	else if (lvl + 1 == len)
		if (select->mln->tern_next->npsb)
			*psb += select->mln->tern_next->npsb;
}

int		ret_psb(t_slct *select, int len, int lvl, char *bru)
{
	if (select->next)
		if (ret_psb(select->next, len, lvl, bru))
			return (1);
	if (select->down)
	{
		bru[lvl] = select->mln->value;
		if (ret_psb(select->down, len, lvl + 1, bru))
			return (1);
	}
	else if (lvl + 1 == len)
		if (select->mln->npsb)
		{
			bru[lvl] = '\0';
			get_tstr(select->mln, bru);
			return (1);
		}
	return (0);
}

void	put_select(t_slct *select, int lvl)
{
	if (select->next)
		put_select(select->next, lvl);
	if (select->down)
		put_select(select->down, lvl + 1);
}
