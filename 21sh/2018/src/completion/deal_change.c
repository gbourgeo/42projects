/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:16:45 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 13:56:03 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"
#include "shell.h"
#include "libft.h"

static void	get_ptr_tree(t_tree *tree, char **ptr)
{
	if (!tree)
		return ;
	if (tree->value == '.')
		if (!tree->left || !tree->right)
			tree->left ? get_ptr_tree(tree->left, ptr)
				: get_ptr_tree(tree->right, ptr);
	if (tree->left && tree->left->value != '.')
		return ;
	if (tree->right && tree->right->value != '.')
		return ;
	if (tree->value == '.')
		return ;
	**ptr = tree->value;
	*ptr += 1;
	if (tree->tern_next)
		get_ptr_tree(tree->tern_next, ptr);
}

static void	get_nb_slct(t_slct *select, int *nb, int *len)
{
	t_tree	*tree;

	if (select->next)
	{
		*nb += 1;
		get_nb_slct(select->next, nb, len);
	}
	if (select->down)
		get_nb_slct(select->down, nb, len);
	else
	{
		tree = select->mln->tern_next;
		while (tree->tern_next)
		{
			*len += 1;
			tree = tree->tern_next;
		}
	}
}

static void	change_ptr(t_slct *select, char **ptr)
{
	if (**ptr == '$')
	{
		*ptr += 1;
		if (**ptr == '{')
			*ptr += 1;
	}
	**ptr = select->mln->value;
	*ptr += 1;
	if (select->down)
		change_ptr(select->down, ptr);
	else
		get_ptr_tree(select->mln->tern_next, ptr);
}

static void	change_select(t_slct *select, int tmp, t_cpl_e *env)
{
	int		len;
	t_line	*line;

	line = get_struct();
	len = 0;
	get_nb_slct(select, &tmp, &len);
	if (tmp == 1)
	{
		if ((len + line->len + line->lprompt) % line->nb_col
				< (line->len + line->lprompt) % line->nb_col)
			tputs(tgetstr("do", NULL), 1, ft_pchar);
		change_ptr(select, &env->ptr);
	}
}

int			deal_change(t_slct *select, t_tree *tern, t_cpl_e *env)
{
	int		tmp;

	tmp = 1;
	if (select)
		change_select(select, tmp, env);
	else if (tern)
	{
		tmp = 0;
		get_tree_psb(tern, &tmp);
		if (tmp == 1)
			return (1);
		get_ptr_tree(tern, &env->ptr);
	}
	return (0);
}
