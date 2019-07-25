/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shake_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 19:44:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 22:12:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static t_tree	*rleft(t_tree *node)
{
	t_tree	*tmp;

	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	ft_hash(tmp->left);
	ft_hash(tmp);
	return (tmp);
}

static t_tree	*rright(t_tree *node)
{
	t_tree	*tmp;

	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	ft_hash(tmp->right);
	ft_hash(tmp);
	return (tmp);
}

static int		count_hash(t_tree *t)
{
	return ((a == NULL) ? -1 : a->hash);
}

t_tree			*ft_shake_tree(char *keyw, char *value, t_tree *node)
{
	ft_hash(node);
	if (count_hash(node->left) - count_hash(node->right) == 2)
	{
		if(count_hash(node->left->left) < count_hash(node->left->right))
			node->left = rleft(node->left);
		return (rright(node));
	}
	if (count_hash(node->left) - count_hash(node->right) == -2)
	{
		if(count_hash(node->right->right) < count_hash(node->right->left))
			node->right = rleft(node->right);
		return (rleft(node));
	}
	return (node);
}
