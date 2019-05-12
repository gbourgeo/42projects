/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:19:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 01:28:13 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

void		count_elem(t_tree *tree, int *cpt)
{
	if (tree->left)
		count_elem(tree->left, cpt);
	if (tree->tern_next && (tree->prev || tree->value != '.'))
		count_elem(tree->tern_next, cpt);
	else if (!tree->tern_next)
	{
		if (tree->tput)
			*cpt += 1;
	}
	if (tree->right)
		count_elem(tree->right, cpt);
}

void		change_elem(t_tree *tree, int val, int *cpt)
{
	if (tree->left)
		change_elem(tree->left, val, cpt);
	if (tree->tern_next && (tree->prev || tree->value != '.'))
		change_elem(tree->tern_next, val, cpt);
	else if (!tree->tern_next)
	{
		if (*cpt == val - 1)
			tree->tput = 0;
		else
		{
			tree->tput = 1;
			*cpt += 1;
		}
	}
	if (tree->right)
		change_elem(tree->right, val, cpt);
}

void		deal_tree_key(t_tree *tree, int nb_col, int key)
{
	int		psb;

	psb = 0;
	get_tree_psb(tree, &psb);
	if (key == DOWN)
		deal_slct_key_down(tree, NULL, psb, nb_col);
	else if (key == UP)
		deal_slct_key_up(tree, NULL, psb, nb_col);
	else if (key == LEFT)
		deal_slct_key_left(tree, NULL, psb);
	else if (key == WINCH)
		deal_slct_winch(tree, NULL);
}

void		deal_slct_key(t_slct *select, int nb_col, int key)
{
	int		tmp;
	t_tree	*tree;

	tree = NULL;
	if (select->down)
		deal_slct_key(select->down, nb_col, key);
	else
	{
		if (select->next)
			tree = select->next->mln->tern_next;
		tmp = select->mln->tern_next->npsb;
		if (select->next)
			tmp += select->next->mln->tern_next->npsb;
		if (key == DOWN)
			deal_slct_key_down(select->mln->tern_next, tree, tmp, nb_col);
		else if (key == UP)
			deal_slct_key_up(select->mln->tern_next, tree, tmp, nb_col);
		else if (key == LEFT)
			deal_slct_key_left(select->mln->tern_next, tree, tmp);
		else if (key == WINCH)
			deal_slct_winch(select->mln->tern_next, tree);
		return ;
	}
	if (select->next)
		deal_slct_key(select->next, nb_col, key);
}
