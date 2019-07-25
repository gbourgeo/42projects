/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_node.c                                :+:      :+:    :+:      */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 04:43:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:52:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int			ft_search_node(t_tree *tree, char *key)
{
	if (tree == NULL)
	{
		ft_putstr(tree->keyw);
		ft_putstr(": Not found.");
		return (0);
	}
	else if (key == tree->keyw)
	{
		ft_putstr(tree->keyw);
		return (0);
	}
	else if (key < tree->keyw)
		return (ft_search_node(tree->left, key));
	return (ft_search_node(tree->right, key));
}
