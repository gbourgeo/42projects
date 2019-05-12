/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_glob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:19:10 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 15:57:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "libft.h"

void	sort_glob(t_slst *glob)
{
	t_slst	*tmp;
	char	*ptr;

	if (!glob)
		return ;
	while (glob->prev)
		glob = glob->prev;
	tmp = glob;
	while (glob->next)
	{
		if (ft_strcmp(glob->str, glob->next->str) > 0)
		{
			ptr = glob->str;
			glob->str = glob->next->str;
			glob->next->str = ptr;
			glob = tmp;
		}
		else
			glob = glob->next;
	}
}

void	get_glob(t_tree *tree, char *tget, t_slist **glob, t_stint sti)
{
	if (!tree)
		return ;
	get_glob(tree->left, tget, glob, sti);
	get_glob(tree->right, tget, glob, sti);
	if (!(tree->value) && *tget == '*')
	{
		if (*(tget + 1) == '*')
			sti.nb |= IS_SLASH;
		while (*tget == '*')
			tget++;
	}
	if ((!(*tget) || *tget == '/') && !(tree->value))
		glob_slash(tree, &tget, glob, &sti);
	else if (*tget == '*')
		glob_star(tree, &tget, glob, &sti);
	else if (*tget == tree->value)
		get_glob(tree->tern_next, tget + 1, glob, sti);
	else if (*tget == '?' && tree->value)
		get_glob(tree->tern_next, tget + 1, glob, sti);
	else if (*tget == '[' && tree->value)
		if (*(tget + 1) == '-' || !glob_brack(tree, tget, glob, sti))
			return ;
	if (*tget == '/' && tree->value)
		get_glob(tree, tget + 1, glob, sti);
}
