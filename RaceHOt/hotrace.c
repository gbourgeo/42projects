/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 22:21:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 20:36:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	destroy_tree(t_list *tree)
{
	if (tree->left != NULL)
	{
		destroy_tree(tree->left);
	}
	if (tree->right != NULL)
	{
		destroy_tree(tree->right);
	}
	free(tree);
}

int				main(void)
{
	char		*keyword;
	char		*value;
	t_list		*result;

	keyword = NULL;
	value = NULL;
	result = NULL;
	while ((get_next_line(0, &keyword)) == 1 && *keyword)
	{
		if ((get_next_line(0, &value)) != 1)
			return (-1);
		ft_add_node(&result, keyword, value);
	}
	while ((get_next_line(0, &keyword)) == 1 && *keyword)
	{
		if ((ft_search_node(result, keyword)) == 1)
			return (-1);
	}
	destroy_tree(result);
	return (0);
}
