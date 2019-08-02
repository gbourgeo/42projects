/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 04:43:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/02 22:59:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_search_node.h"

int			ft_search_node(t_list *tree, char *key)
{
	while (tree)
	{
		if (ft_strcmp(key, tree->keyw) == 0)
		{
			ft_putstr(tree->value);
			ft_putstr("\n");
			return (0);
		}
		if (ft_strcmp(key, tree->keyw) > 0)
			tree = tree->left;
		else
			tree = tree->right;
	}
	ft_putstr(key);
	ft_putstr(": Not found.\n");
	return (0);
}
