/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_put_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:54:10 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 19:15:37 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"
#include "libft.h"

static char	*find_chr_buff(t_line *line)
{
	char	*ptr;

	if (have_to_expand(line))
	{
		return (*(ptr = sh_strrchr(line->curr->buff, '$') + 1) == '{'
				? ptr + 1 : ptr);
	}
	if (!(ptr = sh_strrchr(line->curr->buff, ' ')))
		ptr = line->curr->buff;
	return (sh_strchr(ptr, '/')
			? sh_strrchr(ptr, '/') + 1 : ptr + 1);
}

static int	deal_select(t_slct *select, t_cpl_e env, t_line *line)
{
	int		tres;
	int		psb;

	psb = 0;
	tres = 0;
	get_psb(select, ft_strlen(env.chr), 0, &psb);
	if (psb <= 1)
	{
		if (!ft_strcmp(env.chr, line->curr->buff_tmp))
			ret_psb(select, ft_strlen(env.chr), 0, line->curr->buff);
		else
			ret_psb(select, ft_strlen(env.chr), 0, find_chr_buff(line));
		free(env.chr);
		if (select)
			free_select(select);
		return (1);
	}
	if (line->is_putb && line->key)
		deal_slct_key(select, env.nb_col, line->key);
	get_isput(select, ft_strlen(env.chr), 1, &tres);
	if (!tres)
		reset_isput(select, ft_strlen(env.chr), 1);
	return (0);
}

static int	deal_ret_psb(t_line *line, t_tree *tern, t_cpl_e env)
{
	char	*tmp;
	char	*chr;

	if ((chr = sh_strrchr(line->curr->buff, ' ')))
		tmp = sh_strchr(chr, '/') ? sh_strrchr(chr, '/') : chr;
	else
		tmp = sh_strchr(line->curr->buff, '/')
			? sh_strrchr(line->curr->buff, '/') : line->curr->buff;
	if (tern->value != '.')
		get_tstr(tern, tmp);
	else
		tern->left ? get_tstr(tern->left, tmp) : get_tstr(tern->right, tmp);
	if (env.chr)
		free(env.chr);
	return (1);
}

static int	deal_tree(t_line *line, t_tree *tern, t_cpl_e env)
{
	int		tres;
	int		psb;

	tres = 0;
	psb = 0;
	get_tree_psb(tern, &psb);
	if (psb == 1)
		return (deal_ret_psb(line, tern, env));
	if (line->is_putb && line->key)
		deal_tree_key(tern, env.nb_col, line->key);
	get_put(tern, &tres, *env.chr);
	if (!tres)
		reset_put(tern);
	return (0);
}

int			deal_put(t_line *line, t_cpl_e env, t_slct *select, t_tree *tern)
{
	if (select && deal_select(select, env, line))
		return (1);
	else if (!select && deal_tree(line, tern, env))
		return (1);
	if (select)
		put_select_branch(select, env, line);
	else if (env.lenm)
		put_tree_branch(tern, env, line);
	else
	{
		if (env.chr)
			free(env.chr);
		return (-1);
	}
	return (0);
}
