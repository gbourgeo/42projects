/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:12 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/07 14:24:50 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "globing.h"

static void	rev_brack(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	int		tmp;

	while (*tget && *tget != ']')
	{
		if (*tget == tree->value)
			return ;
		else if (*(tget + 1) == '-')
		{
			tmp = *tget;
			while (tmp <= *(tget + 2))
			{
				if (tmp == tree->value)
					return ;
				tmp++;
			}
			tget += 2;
			if (*tget == tree->value)
				return ;
		}
		tget += 1;
	}
	get_glob(tree->tern_next, tget + 1, glob, sti);
}

static void	norm_brack(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	int		tmp;

	while (*tget && *tget != ']')
	{
		if (*tget == tree->value)
		{
			while (*tget && *tget != ']')
				tget++;
			if (*tget != ']')
				return ;
			get_glob(tree->tern_next, tget + 1, glob, sti);
		}
		else if (*tget == '-')
			while (++tmp <= *(tget + 1))
				if (tmp == tree->value)
				{
					while (*tget && *tget != ']')
						tget++;
					if (*tget != ']')
						return ;
					get_glob(tree->tern_next, tget + 1, glob, sti);
				}
		tget++;
		tmp = *tget - 1;
	}
}

int			glob_brack(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	if (*(tget + 1) == '!')
		rev_brack(tree, tget + 2, glob, sti);
	else
		norm_brack(tree, tget, glob, sti);
	return (1);
}

void		glob_star(t_tree *tree, char **tget, t_slist **glob, t_stint *sti)
{
	if (!tree->prev && tree->value == '.')
		return ;
	get_glob(tree->tern_next, *tget, glob, *sti);
	if (*(*tget + 1) == '*')
		sti->nb |= IS_SLASH;
	while (*(*tget + 1) == '*')
		*tget += 1;
	if (*(*tget + 1) == '?' || *(*tget + 1) == '['
			|| *(*tget + 1) == tree->value)
	{
		sti->nb &= ~IS_SLASH;
		get_glob(tree, *tget + 1, glob, *sti);
	}
}

void		glob_slash(t_tree *tree, char **tget, t_slist **glob, t_stint *sti)
{
	if (**tget == '/' && sti->nb & IS_SLASH)
		sti->nb |= IS_REC;
	while (**tget && *(*tget + 1) == '/')
		*tget += 1;
	get_new_mln(tree, *tget, glob, *sti);
}
