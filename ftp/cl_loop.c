/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 07:07:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void			cl_check_commands(t_envi *cl)
{
	char			**cmds;
	int				i;
	static char		*commands[] = {COMMANDS, CMD_PLUS, 0};
	static int		(*func[])(char **, t_envi *) = {FUNCTIONS, FUNC_PLUS};

	i = 0;
	if ((cmds = ft_split_whitespaces(cl->buff)) == NULL)
		cl_end("\033[31mERROR: Splitting the command failed.", cl);
	if (cmds[0] == NULL)
		return (ft_free(&cmds));
	if (!ft_strcmp(cmds[0], "quit"))
		cl_end(NULL, cl);
	while (commands[i] && ft_strcmp(cmds[0], commands[i]))
		i++;
	if (commands[i])
		cl->success = func[i](cmds, cl);
	else if (cmds[0][0] == 'l')
		cl->success = cl_commands(cmds, cl);
	else
		cl->success = file_error("ERROR: Command not found !", cl, CLIENT, 0);
	ft_free(&cmds);
}

void				cl_loop(t_envi *cl)
{
	cl_prompt(cl);
	while ((cl->rec = read(0, cl->buff, BUFF_SIZE)) > 0)
	{
		if (cl->buff[cl->rec - 1] == '\n')
			cl->buff[cl->rec - 1] = '\0';
		cl_check_commands(cl);
		ft_bzero(cl->buff, BUFF_SIZE);
		cl_prompt(cl);
	}
	if (cl->rec < 0)
		cl_end("\033[31mERROR: client read() fail.", cl);
	else
		cl_end(NULL, cl);
}
