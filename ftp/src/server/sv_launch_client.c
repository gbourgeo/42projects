/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_launch_client.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 23:20:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 09:42:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		ft_aff_tab(char **tab)
{
	int			i;

	i = 0;
	while (tab && tab[i])
	{
		ft_putstr(tab[i]);
		i++;
		if (tab[i])
			write(1, " ", 1);
	}
	if (tab)
		write(1, "\n", 1);
}

static void		sv_check_commands(t_envi *sv)
{
	char			**cmds;
	int				i;
	static char		*commands[] = {COMMANDS, CMD_PLUS, 0};
	static int		(*func[])(char **, t_envi *) = {FUNCTIONS, FUNC_PLUS};

	i = 0;
	if ((cmds = ft_split_whitespaces(sv->buff)) == NULL)
		sv_client_end(NULL, sv);
	while (commands[i] && ft_strcmp(cmds[0], commands[i]))
		i++;
	if (commands[i])
		sv->rec = func[i](cmds, sv);
	ft_aff_tab(cmds);
	ft_free(&cmds);
}

pid_t			sv_launch_client(int cl_fd, t_envi *sv)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		sv->fd = cl_fd;
		while ((sv->rec = recv(sv->fd, sv->buff, BUFF_SIZE, 0)) > 0)
		{
			sv->buff[sv->rec] = '\0';
			sv_check_commands(sv);
			ft_bzero(sv->buff, BUFF_SIZE);
		}
		sv_client_end(NULL, sv);
	}
	else if (sv->success)
		ft_putendn(pid);
	if (pid < 0 && sv->success)
		ft_putendl_fd("SERVEUR: fork() failed launching server", 2);
	return (pid);
}
