/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:37:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/08 16:45:54 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "put.h"

static int	free_null(t_slct **data)
{
	free(*data);
	*data = NULL;
	return (0);
}

static int	deal_upper(t_tree *upper, char *src, int *lenm, t_slct **select)
{
	if (!upper)
		return (1);
	while (upper && upper->value != ft_toupper(*src))
		upper = ft_toupper(*src) < upper->value ? upper->left : upper->right;
	if (upper)
	{
		if (!(src[1]))
			*lenm = upper->max_len > *lenm ? upper->max_len : *lenm;
		if (!(*select = ft_memalloc(sizeof(t_slct))))
			return (0);
		(*select)->mln = upper;
		if (*(src + 1) && !((*select)->down =
					select_branch(upper->tern_next, src + 1, lenm)))
			return (free_null(select));
	}
	return (1);
}

static int	tool_lower(t_tree *lower, char *src, int *lenm, t_slct **select)
{
	if (*select)
	{
		if (!((*select)->next = ft_memalloc(sizeof(t_slct))))
			return (0);
		(*select)->next->prev = *select;
		(*select)->next->mln = lower;
		if (*(src + 1) && !((*select)->next->down =
					select_branch(lower->tern_next, src + 1, lenm)))
			return (free_null((&(*select)->next)));
	}
	else
	{
		if (!(*select = ft_memalloc(sizeof(t_slct))))
			return (0);
		(*select)->mln = lower;
		if (*(src + 1) && !((*select)->down =
					select_branch(lower->tern_next, src + 1, lenm)))
			return (free_null(select));
	}
	return (1);
}

static int	deal_lower(t_tree *lower, char *src, int *lenm, t_slct **select)
{
	while (lower && lower->value != ft_tolower(*src))
		lower = ft_tolower(*src) < lower->value ? lower->left : lower->right;
	if (lower && !(src[1]))
		*lenm = lower->max_len > *lenm ? lower->max_len : *lenm;
	if (lower)
	{
		if (!tool_lower(lower, src, lenm, select))
			return (0);
	}
	return (1);
}

t_slct		*select_branch(t_tree *upper, char *src, int *lenm)
{
	t_slct	*select;
	t_tree	*lower;
	int		up;
	int		low;

	select = NULL;
	lower = upper;
	up = 0;
	low = 0;
	if (*src)
		up = deal_upper(upper, src, lenm, &select);
	if (*src && ft_toupper(*src) != ft_tolower(*src))
		low = deal_lower(lower, src, lenm, &select);
	if (!up && !low)
		return (NULL);
	return (select);
}
