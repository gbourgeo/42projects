/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:31:38 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/07 16:51:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "globing.h"
#ifdef __linux
# define __USE_MISC
# define DT_DIR 4
#endif

static void	get_new_str(t_slist **glob, char *prev)
{
	int		tlen;
	t_tree	*tmp;
	int		i;

	tlen = 0;
	if (prev)
		tlen = ft_strlen(prev) + 1;
	tlen = (*glob)->mln->len + tlen;
	if (!((*glob)->str = ft_memalloc(sizeof(char) * (tlen + 1))))
		return ;
	if (prev)
	{
		i = -1;
		while (prev[++i])
			(*glob)->str[i] = prev[i];
		(*glob)->str[i] = '/';
	}
	tmp = (*glob)->mln;
	(*glob)->str[tlen] = 0;
	while (tmp)
	{
		(*glob)->str[tlen] = tmp->value;
		tmp = tmp->prev;
		tlen--;
	}
}

static int	get_new_glob(t_tree *tree, t_slist **glob)
{
	if (*glob)
	{
		while ((*glob)->prev)
			*glob = (*glob)->prev;
		while ((*glob)->next && (*glob)->mln != tree)
			*glob = (*glob)->next;
		if ((*glob)->mln == tree)
			return (0);
		if (!((*glob)->next = ft_memalloc(sizeof(t_slist))))
			return (0);
		(*glob)->next->prev = *glob;
		*glob = (*glob)->next;
	}
	else
	{
		if (!(*glob = ft_memalloc(sizeof(t_slist))))
			return (0);
	}
	(*glob)->mln = tree;
	return (1);
}

static void	deal_rec(char *str, t_slist **glob, t_stint *sti)
{
	t_tree *tmp;

	if (!(tmp = create_file_tree((*glob)->str, NULL, NULL)))
		return ;
	if (sti->nb & IS_SLASH)
		sti->nb |= IS_REC;
	if (sti->nb & IS_REC)
		get_glob(tmp, "**", glob, *sti);
	else
		get_glob(tmp, str + 1, glob, *sti);
	free_tree(tmp);
}

static void	deal_error_glob(t_slist **glob)
{
	if ((*glob)->prev)
	{
		*glob = (*glob)->prev;
		free((*glob)->next);
		(*glob)->next = NULL;
	}
	else
	{
		free(*glob);
		*glob = NULL;
	}
}

void		get_new_mln(t_tree *tree, char *str, t_slist **glob, t_stint sti)
{
	DIR			*dir;
	t_stint		si_tmp;

	if (*str == '/' && !(tree->type & DT_DIR) && !*(str + 1))
		return ;
	if (*str == '/' && sti.nb & IS_SLASH)
		sti.nb |= IS_REC;
	if (get_new_glob(tree, glob) == 0)
		return ;
	get_new_str(glob, sti.str);
	if (!(*glob)->str)
	{
		deal_error_glob(glob);
		return ;
	}
	si_tmp.str = ft_strdup((*glob)->str);
	si_tmp.nb = sti.nb;
	if ((dir = opendir((*glob)->str)) && ((*str == '/' && *(str + 1))
				|| sti.nb & IS_REC))
		deal_rec(str, glob, &si_tmp);
	free(si_tmp.str);
	if (dir)
		closedir(dir);
}
