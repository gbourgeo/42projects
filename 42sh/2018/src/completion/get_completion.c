/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 03:41:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/23 14:06:44 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"
#include "shell.h"
#include "libft.h"

static void		deal_choose_tree(t_line *line, char *ptr)
{
	if (!line->term)
		return ;
	if (have_to_expand(line))
		deal_complet(GET_TREE(line->tree, ENV), line);
	else if (check_is_file(line->curr->buff, line))
	{
		if (!ptr)
			ptr = line->curr->buff;
		if (search_to_tmp(ptr))
		{
			if (!(*line->e_cmpl & COMPLETION))
				GET_TREE(line->tree, TMP) =
					free_tree(GET_TREE(line->tree, TMP));
			if (GET_TREE(line->tree, TMP)
					|| (GET_TREE(line->tree, TMP) =
						set_tmp(line->curr->buff, 0)))
				deal_complet(GET_TREE(line->tree, TMP), line);
		}
		else
			deal_complet(GET_TREE(line->tree, FILES), line);
	}
	else
		deal_complet(GET_TREE(line->tree, BIN), line);
}

static t_slst	*choose_globing(t_line *line, char *ptr)
{
	t_slst	*tmp;
	char	*str;

	tmp = NULL;
	if (search_to_tmp(ptr))
	{
		GET_TREE(line->tree, TMP) = free_tree(GET_TREE(line->tree, TMP));
		if ((GET_TREE(line->tree, TMP) = set_tmp(line->curr->buff, 1)))
		{
			if (*ptr == '~')
				str = replace_tilde(ptr, getenv("HOME"));
			else
				str = ft_strdup(ptr);
			tmp = deal_globing(str, GET_TREE(line->tree, TMP));
			free(str);
		}
	}
	else
		tmp = deal_globing(ptr, GET_TREE(line->tree, FILES));
	return (tmp);
}

static void		choose_tree(t_line *line)
{
	char	*ptr;
	t_slst	*tmp;

	tmp = NULL;
	if ((ptr = sh_strrchr(line->curr->buff, ' ')) && str_chrglob(ptr))
		tmp = choose_globing(line, ptr + 1);
	else if (!ptr && str_chrglob(line->curr->buff))
		tmp = choose_globing(line, line->curr->buff);
	else
		deal_choose_tree(line, ptr);
	if (!ptr)
		set_new_glob(line, tmp, 0);
	else
		set_new_glob(line, tmp, ptr - line->curr->buff + 1);
}

void			get_complet(t_line *line)
{
	if (!(*line->e_cmpl & COMPLETION)
			&& line->curr->buff_tmp)
	{
		free(line->curr->buff_tmp);
		line->curr->buff_tmp = NULL;
	}
	if (!inprint(line->curr->buff))
		return ;
	choose_tree(line);
}
