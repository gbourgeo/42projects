/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpl_select_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:21:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 01:44:04 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

void		deal_slct_key_left(t_tree *select, t_tree *tree, int nb_elem)
{
	int		cpt;
	int		flg;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	if (cpt == 1 || cpt == 0)
		cpt = nb_elem + 1;
	change_elem(select, cpt - 1, &flg);
	if (tree)
		change_elem(tree, cpt - 1, &flg);
}

void		deal_slct_key_up(t_tree *select, t_tree *tree,
		int nb_elem, int nb_col)
{
	int		cpt;
	int		flg;
	int		tmp;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	if (cpt - nb_col <= 0)
	{
		tmp = cpt % nb_col;
		cpt = nb_elem;
		while (cpt % nb_col != tmp)
			cpt--;
		cpt += nb_col;
	}
	change_elem(select, cpt - nb_col, &flg);
	if (tree)
		change_elem(tree, cpt - nb_col, &flg);
}

void		deal_slct_key_down(t_tree *select, t_tree *tree,
		int nb_elem, int nb_col)
{
	int		cpt;
	int		flg;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	if (cpt + nb_col > nb_elem)
	{
		if (cpt % nb_col == 0)
			cpt = 0;
		else
			cpt = cpt % nb_col - nb_col;
	}
	change_elem(select, cpt + nb_col, &flg);
	if (tree)
		change_elem(tree, cpt + nb_col, &flg);
}

void		deal_slct_winch(t_tree *select, t_tree *tree)
{
	int		cpt;
	int		flg;

	cpt = 0;
	flg = 0;
	count_elem(select, &cpt);
	if (tree)
		count_elem(tree, &cpt);
	reset_put(select);
	if (tree)
		reset_put(tree);
	change_elem(select, cpt, &flg);
	if (tree)
		change_elem(tree, cpt, &flg);
}
