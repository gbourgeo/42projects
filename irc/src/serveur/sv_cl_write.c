/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:15:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 18:13:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_aff_wr(int i, char *wr)
{
	write(1, "\nClient ", 8);
	ft_putnbr(i);
	write(1, " wr: ", 5);
	write(1, wr, BUFF);
}

static void		sv_null(char **cmds, t_env *e, size_t i)
{
	if (ft_strcmp(cmds[0], "/connect"))
		send(e->fds[i].fd, "\e[31mCommand not found.\n\e[0m", 28, 0);
}

static void		sv_cmd_client(t_env *e, int i)
{
	char		**cmds;
	int			nb;
	static void	(*fct[])(char **, t_env *, size_t) = { SV_FUNCT1, SV_FUNCT2 };
	static char	*name[] = { COMMANDS1, COMMANDS2 };

	nb = 0;
	if ((cmds = sv_split(&e->fds[i].wr)) == NULL)
		return (sv_error("Server: splitting command failed\n", NULL));
	while (name[nb] && ft_strcmp(name[nb], cmds[0]))
		nb++;
	fct[nb](cmds, e, i);
	ft_free(&cmds);
	if (nb == 7)
		return ;
	send(e->fds[i].fd, END_CHECK, END_CHECK_LEN, 0);
}

void			sv_cl_write(t_env *e, size_t i)
{
	char		tmp[NAME_SIZE + 14];

	if (e->fds[i].wr.tail && *e->fds[i].wr.tail == '\n')
	{
		if (*e->fds[i].wr.head == '/')
			sv_cmd_client(e, i);
		else if (*e->fds[i].wr.head != '\n')
		{
			tmp[0] = '\n';
			ft_strncpy(&tmp[1], e->fds[i].name, NAME_SIZE);
			ft_strcat(tmp, " \e[31m<\e[0m ");
			sv_send_to_chan(tmp, e, i);
		}
		if (e->fds[i].wr.tail)
			*e->fds[i].wr.tail = '\0';
		if (e->verb)
			sv_aff_wr(i, e->fds[i].wr.start);
		e->fds[i].wr.head = e->fds[i].wr.tail;
	}
}
