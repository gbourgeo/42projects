/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 03:06:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:26:41 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"
#include "put.h"
#include "shell.h"

void	reset_put(t_tree *tern)
{
	if (!tern)
		return ;
	if (tern->left)
		reset_put(tern->left);
	if (tern->right)
		reset_put(tern->right);
	if (tern->tern_next)
		reset_put(tern->tern_next);
	if (tern && !tern->tern_next)
		tern->tput = 0;
}

void	deal_reset(t_tree **tree)
{
	if (tree[0])
		reset_put(tree[0]);
	if (tree[1])
		reset_put(tree[1]);
	if (tree[2])
		reset_put(tree[2]);
	if (tree[3])
		reset_put(tree[3]);
}
