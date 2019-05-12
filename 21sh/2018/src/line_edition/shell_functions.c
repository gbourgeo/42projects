/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:10:26 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 21:58:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "shell_lib.h"
#include "history.h"
#include "main_tools.h"
#include "job_control.h"

static void		get_cursor_pos(void)
{
	static char	cmd[] = "\033[6n";
	char		buf[15];
	int			nb_read;
	char		*ptr;

	ft_memset(buf, 0, sizeof(buf));
	write(STDIN_FILENO, cmd, sizeof(cmd));
	if ((nb_read = read(STDIN_FILENO, buf, sizeof(buf) - 1)) < 0)
		return ;
	buf[nb_read] = 0;
	if (!(ptr = ft_strchr(buf, ';')))
		return ;
	ptr++;
	if (ft_atoi(ptr) == 1)
		return ;
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	tputs("%", 1, ft_pchar);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	tputs("\n", 1, ft_pchar);
}

static void		get_new_cmd(t_line *line, t_s_env *e)
{
	char		*ret;

	go_end(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ret = ft_strdup(line->curr->buff);
	*(line->e_cmpl) &= ~COMPLETION;
	launch_new_cmd(&ret, e);
	get_cursor_pos();
	if (ret)
		save_history(line, ret, &(line->hist), e->public_env);
	ft_strdel(&ret);
	init_new_buff(line);
	del_all_state(line);
	reset_hist(line);
	GET_TREE(line->tree, FILES) = free_tree(line->tree[1]);
	GET_TREE(line->tree, FILES) = create_file_tree(".", NULL, line->tree[1]);
}

void			init_shell_line(t_line **line, t_s_env *e)
{
	if (!(*line = get_struct()))
	{
		free_shell_env(e);
		exit(1);
	}
	(*line)->public_env = &e->public_env;
	(*line)->private_env = &e->private_env;
	if (!((*line)->curr = ft_memalloc(sizeof(t_buff)))
			|| init_line(e->public_env, *line))
	{
		free(line);
		free_shell_env(e);
		exit(1);
	}
}

void			shell_loop(t_line *line, t_s_env *e)
{
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	while (e->shell_loop && line->shell_loop)
	{
		jobs_remove(&e->jobs, 1);
		if (line->tmp[0] == -1)
			*e->ret = 130;
		put_prompt(line->prompt, *line->ret);
		deal_typing(line);
		write(STDIN_FILENO, "\n", 1);
		if (line->curr->buff && line->curr->buff[0] && line->tmp[0] != -1
				&& line->curr->buff[0] != 10)
			get_new_cmd(line, e);
		jobs_notify_ended(e->jobs, e);
		if (line->path)
			check_mod_path(e, line, 0);
	}
}
