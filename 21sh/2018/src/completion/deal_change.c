/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:16:45 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/18 12:59:32 by rfontain         ###   ########.fr       */
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
			tree->left ?
				get_ptr_tree(tree->left, ptr) : get_ptr_tree(tree->right, ptr);
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

static void	get_nb_slct(t_slct *select, int *nb)
{
	if (select->next)
	{
		*nb += 1;
		get_nb_slct(select->next, nb);
	}
	if (select->down)
		get_nb_slct(select->down, nb);
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

static int	deal_change(t_slct *select, t_tree *tern, t_cpl_e *env)
{
	int		tmp;

	tmp = 1;
	if (select)
	{
		get_nb_slct(select, &tmp);
		if (tmp == 1)
			change_ptr(select, &env->ptr);
	}
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

void		change_buff(t_slct *select, t_cpl_e *env, t_line *line,
		t_tree *tern)
{
	char	*ptr;

	ptr = sh_strrchr(line->curr->buff, ' ');
	if (!ptr || !(env->ptr = sh_strrchr(ptr, '/')))
		env->ptr = find_start_pos(line->curr->buff, line);
	if (ft_strchr("&;|/ ", *env->ptr))
		env->ptr += 1;
	if (deal_change(select, tern, env))
		return ;
}
