/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:42:50 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 16:23:42 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "shell.h"
#include "shell_lib.h"
#include "main_tools.h"
#include "put.h"
#include "history.h"

static void	create_all_tree(t_line *line)
{
	free_all_tree(line);
	if (sh_getnenv("PATH", *line->public_env))
		GET_TREE(line->tree, BIN) = create_bin_tree(*line->public_env);
	else if (sh_getnenv("PATH", *line->private_env))
		GET_TREE(line->tree, BIN) = create_bin_tree(*line->private_env);
	GET_TREE(line->tree, FILES) = create_file_tree(".", NULL, NULL);
	GET_TREE(line->tree, TMP) = NULL;
	get_tree_env();
}

int			init_line(char **env, t_line *line)
{
	if (!(line->e_cmpl = ft_memalloc(sizeof(t_st))))
		return (1);
	if (!(line->curr->buff = ft_memalloc(sizeof(char) * MAX_SHELL_LEN)))
		return (1);
	line->path = sh_getnenv("PATH", env);
	line->term = getenv("TERM");
	tgetent(NULL, line->term);
	create_hist(&(line->hist), env);
	if (line->hist)
		line->hist = line->hist->begin;
	tcgetattr(0, &line->save);
	create_all_tree(line);
	line->prompt = ft_strdup("$> ");
	line->lprompt = ft_strlen(line->prompt);
	line->nb_col = tgetnum("co");
	line->nb_line = tgetnum("li");
	line->slct_beg = -1;
	line->slct_end = -1;
	line->shell_loop = 1;
	return (0);
}

void		deal_key(t_line *line)
{
	int				i;
	static t_fctn	fctn[] = {
		{ CANCEL, &deal_cancel }, { EXIT, &deal_exit },
		{ GET_COMPLETION, &get_complet }, { CLEAR, &ft_clear },
		{ DELETE_LEFT, &deal_dleft }, { UP_ARROW, &up_arrow },
		{ DOWN_ARROW, &down_arrow }, { RIGHT_ARROW, &right_arrow },
		{ LEFT_ARROW, &left_arrow }, { GO_END, &go_end },
		{ GO_HOME, &deal_home }, { DELETE_RIGHT, &del_right },
		{ SELECT_LEFT, &select_left}, { SELECT_RIGHT, &select_right},
		{ SELECT_UP, &select_up}, { SELECT_DOWN, &select_down},
		{ NEXT_WORD, &next_word }, { PREV_WORD, &prev_word },
		{ COPY, &ft_copy }, { PASTE, &ft_paste }, { CUT, &ft_cut },
		{ MOVE_UP, &mv_line_up}, { MOVE_DOWN, &mv_line_down} };

	i = -1;
	while (++i < (int)(sizeof(fctn) / sizeof(*fctn)))
		if (ft_strcmp(line->tmp, fctn[i].key) == 0)
		{
			if (line->term || i == 0 || i == 1)
				fctn[i].f(line);
			return ;
		}
}

void		check_path(t_s_env *e)
{
	char	*path;
	t_line	*line;

	line = get_struct();
	path = sh_getnenv("PATH", e->public_env);
	free_tree(line->tree[0]);
	line->tree[0] = create_bin_tree(e->public_env);
	fill_alias_tree(e->alias_list, line);
	line->path = path;
}
