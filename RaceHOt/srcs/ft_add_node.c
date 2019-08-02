/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 23:49:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/02 22:58:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_add_node.h"

int			ft_add_node(t_list **tree, char *key, char *value)
{
	t_list		*node;
	t_list		*tmp;

	if ((node = (t_list*)malloc(sizeof(*node))) == NULL)
		return (-1);
	node->keyw = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	tmp = *tree;
	if (tmp)
		find_null_node(tmp, node);
	else
		*tree = node;
	return (0);
}

static int	find_null_node(t_list *tmp, t_list *node)
{
	t_list		*tmp2;

	while (tmp)
	{
		tmp2 = tmp;
		if ((ft_strcmp(node->keyw, tmp->keyw)) < 0)
		{
			tmp = tmp->right;
			if (!tmp)
				tmp2->right = node;
		}
		else if ((ft_strcmp(node->keyw, tmp->keyw)) == 0)
		{
			tmp2->value = node->value;
			return (0);
		}
		else if ((ft_strcmp(node->keyw, tmp->keyw)) > 0)
		{
			tmp = tmp->left;
			if (!tmp)
				tmp2->left = node;
		}
	}
	return (0);
}
