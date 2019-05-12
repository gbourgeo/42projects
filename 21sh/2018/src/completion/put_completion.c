/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:42:34 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 19:17:07 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"

void		change_buff(t_slct *select, t_cpl_e *env, t_line *line,
		t_tree *tern)
{
	char	*ptr;

	ptr = sh_strrchr(line->curr->buff, ' ');
	if (!ptr || !(env->ptr = sh_strrchr(ptr, '/')))
		env->ptr = find_start_pos(line->curr->buff);
	if (ft_strchr("&;|/ ", *env->ptr))
		env->ptr += 1;
	if (deal_change(select, tern, env))
		return ;
}

void		deal_all_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env)
{
	int		psb;

	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	ft_putendl("");
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putendl("");
	psb = 1;
	env->put = &psb;
	env->nb_col = line->nb_col / (env->lenm + 1);
	env->len = ft_strlen(env->chr);
	deal_put(line, *env, *select, tern);
	if (*select)
		free_select(*select);
	*select = NULL;
	if (env->chr)
		free(env->chr);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	line->is_putb = 0;
	*line->e_cmpl &= ~COMPLETION;
}

int			check_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env)
{
	int		psb;

	psb = 0;
	if (!*select)
		get_tree_psb(tern, &psb);
	else
		get_psb(*select, ft_strlen(env->chr), 0, &psb);
	psb *= env->lenm;
	if (psb > (int)(line->nb_col * (line->nb_line - 3)))
	{
		deal_all_put(line, tern, select, env);
		return (1);
	}
	return (0);
}

static int	end_put(t_line *line, t_cpl_e env, t_slct *select)
{
	if (*line->e_cmpl & COMPLETION)
		if (line->is_putb <= 1)
			line->is_putb += 1;
	*(line->e_cmpl) |= COMPLETION;
	if (env.chr)
		free(env.chr);
	if (select)
		free_select(select);
	select = NULL;
	return (0);
}

int			put_complet(t_tree *tern, int *put, t_line *line, int *nb_ret)
{
	t_slct	*select;
	t_cpl_e	env;
	int		ret;

	env.chr = NULL;
	env.bru[0] = 0;
	select = NULL;
	env.nb_ret = nb_ret;
	if ((env.lenm = get_select(line, tern, &env, &select)) == -1
			|| env.lenm + line->len > MALLOC_MAX)
		return (-1);
	env.put = put;
	env.nb_ret = nb_ret;
	env.nb_col = line->nb_col / (env.lenm + 1);
	env.len = ft_strlen(env.chr);
	if ((env.lenm + line->lprompt + line->len) % line->nb_col
			< (line->lprompt + line->len) % line->nb_col && !line->is_putb
			&& *line->e_cmpl & COMPLETION)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	if ((ret = deal_put(line, env, select, tern)))
		return (ret);
	return (end_put(line, env, select));
}
