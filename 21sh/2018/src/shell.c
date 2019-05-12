/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:46:11 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 13:36:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "shell_env.h"
#include "shell_term.h"
#include "token.h"
#include "job_control.h"
#include "main_tools.h"

int				main(int ac, char **av, char **ep)
{
	t_line		*line;
	t_s_env		e;
	int			ret;

	if (MAX_SHELL_LEN > 10000 || MAX_SHELL_LEN < 100)
		return (1);
	ret = 0;
	line = NULL;
	init_shell_env(&e, ac, av, ep);
	e.ret = &ret;
	init_shell_line(&line, &e);
	line->ret = &ret;
	define_new_term(&e.save);
	if (!av[1])
	{
		get_rc(&e, NULL);
		shell_loop(line, &e);
	}
	else
		get_rc(&e, av[1]);
	term_restore(&e.save);
	check_mod_path(&e, line, 1);
	free_shell_env(&e);
	free_struct(line);
	return (ret);
}
