/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 18:11:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include "common.h"

/*
** Neagative value of any of this defines will lead to unexpected errors !!!
*/

/*
** MAX_CLIENT		Set the number of clients this program will handle. It can't
**					be over the system limit. (see RLIMIT_NOFILE)
*/

# define MAX_CLIENT 42

/*
** MAX_CLIENT_BY_IP Let you choose how many times a same IP can connect.
*/

# define MAX_CLIENT_BY_IP 10

/*
** FLOOD_SPEED		Define the interval in seconds that each writes from the
**					same is considered as flood.
**					Over this interval, the flood value is reinitialized to 0.
**					Example: 3 -> from the last writes plus 3 seconds, each
**					writes will rize the flood value.
*/

# define FLOOD_SPEED 1

/*
** FLOOD_WARNING	Define the number of times a client can flood before being
**					warned.
*/

# define FLOOD_WARNING 3

/*
** FLOOD_KICK		Number of times a user is warned before being kicked.
*/

# define FLOOD_KICK 3

enum
{
	FD_FREE,
	FD_SERVER,
	FD_CLIENT
};

typedef struct			s_fd
{
	int					fd;
	char				addr[46];
	int					type;
	time_t				time;
	char				flood;
	char				name[NAME_SIZE + 1];
	char				chan[CHAN_SIZE + 1];
	void				(*fct_read)();
	void				(*fct_write)();
	t_buf				rd;
	t_buf				wr;
	char				buf_read[BUFF + 1];
	char				buf_write[BUFF + 1];
}						t_fd;

typedef struct			s_chan
{
	char				name[CHAN_SIZE + 1];
	size_t				users;
	struct s_chan		*next;
}						t_chan;

typedef struct			s_env
{
	char				verb;
	size_t				members;
	size_t				maxfd;
	t_fd				fds[MAX_CLIENT + 1];
	t_chan				*chan;
	fd_set				fd_read;
	fd_set				fd_write;
}						t_env;

void					sv_error(char *str, t_env *e);
void					sv_getaddrinfo(char *service, t_env *e, int on);
void					sv_accept(t_env *e);
int						sv_loop(t_env *e);
void					sv_end(char *msg, t_env *e);
void					sv_cl_read(t_env *e, int i);
void					sv_cl_write(t_env *e, size_t i);
void					sv_send_msg(char *msg, t_env *e, size_t i);
void					sv_send_to_chan(char *head, t_env *e, size_t i);
int						sv_flood_protect(t_env *e, int id);
void					sv_nick(char **cmds, t_env *e, size_t i);
void					sv_join(char **cmds, t_env *e, size_t i);
void					sv_leave(char **cmds, t_env *e, size_t i);
void					sv_remove_chan(char *name, t_env *e);
void					sv_leave_chan(t_env *e, size_t i);
void					sv_msg(char **cmds, t_env *e, size_t i);
void					sv_who(char **cmds, t_env *e, size_t i);
void					sv_list(char **cmds, t_env *e, size_t i);
void					sv_help(char **cmds, t_env *e, size_t i);
void					sv_connect(char **cmds, t_env *e, size_t i);
void					sv_cl_end(char **cmds, t_env *e, size_t i);
char					**sv_split(t_buf *buf);
char					*sv_strchr(const t_buf *b, int c);

#endif
