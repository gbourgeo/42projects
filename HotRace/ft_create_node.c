/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                    :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 23:49:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:38:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_tree		*ft_create_node(char *k, char *v, t_tree *left, t_tree *right)
{
	t_tree		*node;

	if ((node = (t_tree*)malloc(sizeof(*node))) == NULL)
		return (NULL);
	node->keyw = k;
	node->value = v;
	node->left = left;
	node->right = right;
	ft_hash(node);
	return (node);
}
