/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/06 17:06:36 by gbourgeo         ###   ########.fr       */
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

static int			client_info(t_client *cl)
{
	if (!(cl->server.pwd = ft_strdup("/")))
		return (ERR_MALLOC);
	if (!(cl->pwd = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	cl->success = 1;
	return (IS_OK);
}

void			cl_prompt(t_client *cl)
{
	printf(COLOR_RESET"Server: "COLOR_GREEN"%s"COLOR_RESET"\n"
	"Client: "COLOR_PINK"%s"COLOR_RESET"\n"
	"%s > "COLOR_RESET,
	cl->server.pwd, cl->pwd, (!cl->success) ? COLOR_RED : COLOR_GREEN);
	fflush(stdout);
}

int					cl_client_loop(t_client *cl)
{
	int			ret;
	char		buff[CMD_BUFF_SIZE];
	int			errnb;

	if ((errnb = client_info(cl)) != IS_OK)
		return (errnb);
	cl_prompt(cl);
	while ((ret = read(0, buff, CMD_BUFF_SIZE)) > 0)
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
