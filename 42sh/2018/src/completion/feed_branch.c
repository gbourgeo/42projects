/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:06:53 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:22:11 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "put.h"

static void	create_new_branch(t_tree **tern, t_tree *prev, char *str, int lvl)
{
	int		len;

	if (!(*tern = ft_memalloc(sizeof(t_tree))))
		return ;
	if (*str < prev->value)
		prev->left = *tern;
	else
		prev->right = *tern;
	(*tern)->value = *str;
	(*tern)->prev = prev->prev;
	if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
		(*tern)->max_len = lvl + len;
}

static void	feed_branch(t_tree **tern, char *str, int lvl)
{
	t_tree	*prev;
	int		len;

	prev = NULL;
	while (*tern && (*tern)->value != *str)
	{
		prev = *tern;
		(*tern) = (*str < (*tern)->value) ? (*tern)->left : (*tern)->right;
	}
	if (!(*tern))
		create_new_branch(tern, prev, str, lvl);
	else
	{
		if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
			(*tern)->max_len = lvl + len;
	}
}

static void	set_new_mln(t_tree **tern, char *str, int lvl, unsigned int type)
{
	int		len;

	(*tern)->value = *str;
	if (!*str)
	{
		(*tern)->len = lvl;
		(*tern)->type = type;
	}
	if (lvl + (len = ft_strlen(str)) > (*tern)->max_len)
		(*tern)->max_len = lvl + len;
}

void		feed_tree(char *str, unsigned char type, t_tree **tern, int lvl)
{
	t_tree		*begin;

	begin = NULL;
	if ((*tern)->value >= 0)
	{
		begin = *tern;
		feed_branch(tern, str, lvl);
	}
	else
		set_new_mln(tern, str, lvl, type);
	if (!(*tern)->tern_next && *str)
	{
		if (!((*tern)->tern_next = ft_memalloc(sizeof(t_tree))))
			return ;
		(*tern)->tern_next->prev = (*tern);
		(*tern)->tern_next->value = -1;
	}
	if (*str)
		feed_tree(str + 1, type, &((*tern)->tern_next), lvl + 1);
	*tern = begin ? begin : *tern;
}
