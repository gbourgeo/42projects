/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:46:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/25 18:16:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MAIN_H
# define CL_MAIN_H

# include "common.h"

# define CONNECT	{ "CONNECT", cl_connect }
# define HELP		{ "HELP", cl_help }
# define NICK		{ "NICK", cl_nick }
# define PASS		{ "PASS", cl_pass }
# define QUIT		{ "QUIT", cl_quit }
# define USER		{ "USER", cl_user }
# define END		{ NULL, cl_nosuchcommand }

# define ERR_NEEDMOREPARAMS " :Not enough parameters."

typedef struct		s_client
{
	int				sock;
	fd_set			fds;
	char			*pass;
	char			**user;
	char			nick[NICK_LEN + 1];
	char			read[BUFF + 1];
	char			write[BUFF + 1];
}					t_client;

typedef struct		s_cmd
{
	char			*name;
	void			(*fct)(char **, t_client *);
}					t_cmd;

int					cl_getaddrinfo(char *addr, char *port, t_client *cl);
int					cl_error(const char *err, t_client *cl);
void				read_client(t_client *cl);
void				read_server(t_client *cl);

int					cl_get(t_client *cl);
int					cl_put(t_client *cl);
void				cl_send(int fd, char *cmd, char *param, char **next);

void				cl_connect(char **cmds, t_client *cl);
void				cl_help(char **cmds, t_client *cl);
void				cl_nick(char **cmds, t_client *e);
void				cl_nosuchcommand(char **cmds, t_client *e);
void				cl_pass(char **cmds, t_client *cl);
void				cl_quit(char **cmds, t_client *cl);
void				cl_user(char **cmds, t_client *cl);

#endif
