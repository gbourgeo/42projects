/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:57:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:27:25 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "struct.h"
#include "shell.h"

static void	get_psblty(t_tree *tern, int *nb, int set)
{
	if (tern->right)
		get_psblty(tern->right, nb, set);
	if (tern->left)
		get_psblty(tern->left, nb, set);
	if (tern->tern_next)
		get_psblty(tern->tern_next, nb, set);
	if (!tern->tern_next)
	{
		if (set)
			tern->type = -1;
		*nb += 1;
	}
}

void		set_psblty(t_tree *tern, int set)
{
	if (tern->right)
		set_psblty(tern->right, set);
	if (tern->left)
		set_psblty(tern->left, set);
	if (tern->tern_next)
		set_psblty(tern->tern_next, set);
	get_psblty(tern, &(tern->npsb), set);
}

void		*free_tree(t_tree *tern)
{
	if (tern)
	{
		if (tern->left)
			free_tree(tern->left);
		if (tern->right)
			free_tree(tern->right);
		if (tern->tern_next)
			free_tree(tern->tern_next);
		free(tern);
	}
	return (NULL);
}

void		free_all_tree(t_line *line)
{
	if (line->tree[0])
		line->tree[0] = free_tree(line->tree[0]);
	if (line->tree[1])
		line->tree[1] = free_tree(line->tree[1]);
	if (line->tree[2])
		line->tree[2] = free_tree(line->tree[2]);
	if (line->tree[3])
		line->tree[3] = free_tree(line->tree[3]);
}
