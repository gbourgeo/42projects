/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_select_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:40:31 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 17:51:24 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell.h"
#include "libft.h"
#include "shell_lib.h"
#include "shell_term.h"

static int	check_select(t_tree *tern, t_cpl_e *env, t_slct **select)
{
	int		lenm;

	lenm = 0;
	if (!(*select = select_branch(tern, env->chr, &lenm)))
	{
		free(env->chr);
		return (-1);
	}
	return (lenm);
}

static int	deal_expand(t_line *line, t_tree *tern, t_cpl_e *env,
		t_slct **select)
{
	int		lenm;

	lenm = 0;
	env->ptr = sh_strrchr(line->curr->buff_tmp, '$');
	if (!*(env->ptr + 1) || (*(env->ptr + 1) == '{' && !*(env->ptr + 2)))
	{
		env->chr = ft_strdup(line->curr->buff_tmp);
		get_max_len(tern, &lenm);
	}
	else
	{
		env->chr = *(env->ptr + 1) == '{' ? ft_strdup(env->ptr + 2)
			: ft_strdup(env->ptr + 1);
		lenm = check_select(tern, env, select);
	}
	return (lenm);
}

char		*find_separator(char *buff)
{
	int		i;

	i = ft_strlen(buff) - 1;
	while (i >= 0)
	{
		if (ft_strchr(";&| /", buff[i]) && (i == 0 || buff[i - 1] != '\\'))
			return (&buff[i + 1]);
		i--;
	}
	return (buff);
}

static int	get_select_tool(t_line *line, t_tree *tern, t_cpl_e *env,
		t_slct **select)
{
	int		lenm;
	char	*ptr;

	lenm = 0;
	ptr = find_separator(line->curr->buff_tmp);
	env->chr = ft_strdup(ptr);
	if (!*env->chr)
		get_max_len(tern, &lenm);
	else
		lenm = check_select(tern, env, select);
	return (lenm);
}

int			get_select(t_line *line, t_tree *tern, t_cpl_e *env,
		t_slct **select)
{
	int		lenm;

	lenm = 0;
	if ((env->is_dol = have_to_expand(line)))
		lenm = deal_expand(line, tern, env, select);
	else if (!(env->ptr = sh_strrchr(line->curr->buff_tmp, ' ')))
		lenm = get_select_tool(line, tern, env, select);
	else if (*(env->chr = !sh_strchr(env->ptr, '/') ? ft_strdup(env->ptr + 1)
				: ft_strdup(sh_strrchr(line->curr->buff_tmp, '/') + 1)))
	{
		free(env->chr);
		lenm = get_select_tool(line, tern, env, select);
	}
	else
		get_max_len(tern, &lenm);
	env->lenm = lenm;
	if (lenm == -1 || check_put(line, tern, select, env))
		return (-1);
	change_buff(*select, env, line, tern);
	return (lenm);
}
