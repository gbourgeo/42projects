/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:42:50 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/16 18:21:14 by rfontain         ###   ########.fr       */
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
	fill_tree_env(*line->public_env, &GET_TREE(line->tree, ENV));
	fill_tree_env(*line->private_env, &GET_TREE(line->tree, ENV));
	if (GET_TREE(line->tree, ENV))
		set_psblty(GET_TREE(line->tree, ENV), 1);
}

void		init_line(char **env, t_line *line)
{
	line->e_cmpl = ft_memalloc(sizeof(t_st));
	line->path = getenv("PATH");
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

void		check_path(t_line *line, char **env)
{
	char	*path;

	path = sh_getnenv("PATH", env);
	if ((path && line->path && ft_strcmp(path, line->path) != 0) || !path)
	{
		free_tree(line->tree[0]);
		line->tree[0] = create_bin_tree(env);
		line->path = path;
	}
}
