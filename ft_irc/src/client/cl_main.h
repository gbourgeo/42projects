/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:46:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 16:18:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MAIN_H
# define CL_MAIN_H

# include "common.h"

typedef struct		s_client
{
	int				first;
	int				sock;
	fd_set			fds;
	char			name[NAME_SIZE + 1];
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
void				cl_loop(t_client *cl);
void				read_client(t_client *cl);
void				read_server(t_client *cl);
int					cl_get(t_client *cl);
int					cl_put(t_client *cl);
void				cl_nick(char **cmds, t_client *e);
void				cl_void(char **cmds, t_client *cl);
void				cl_quit(char **cmds, t_client *cl);
void				cl_help(char **cmds, t_client *cl);
void				cl_connect(char **cmds, t_client *cl);

#endif
