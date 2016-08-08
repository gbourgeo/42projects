/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/02 16:50:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include "common.h"
# include <netinet/in.h>

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

# define MAX_CLIENT_BY_IP 2

/*
** SERV_SIZE		The maximum lenght a servers' name can be. Over this value, a
**					server name will be truncated.
*/

# define SERV_SIZE	20

/*
** CHAN_SIZE		The maximum lenght a channels' name can be. Over this value, a
**					channel name will be truncated.
*/

# define CHAN_SIZE	50

/*
** TOPIC_SIZE		The maximum lenght of a topic. Over this value, the
**					topic will be truncated.
*/

# define TOPIC_SIZE	80

/*
** FLOOD_SPEED		Define the interval in seconds that each writes from the
**					same is considered as flood.
**					Over this interval, the flood value is reinitialized to 0.
**					Example: 3 -> from the last writes plus 3 seconds, each
**					writes will rize the flood value.
*/

# define FLOOD_SPEED 2

/*
** FLOOD_WARNING	Define the time in seconds a client can send before being
**					warned.
*/

# define FLOOD_WARNING 3

/*
** FLOOD_KICK		Number of times a user is warned before being kicked.
*/

# define FLOOD_KICK 3

/*
** User flags.
*/

# define CHFL_CHANOP 0x0001
# define FLAGS_AWAY  0x0020

# define ISVALID(c) (((c) >= 'A' && (c) <= '~') || ft_isdigit(c) || (c) == '-')
# define ISCHAN(c) (*c == '#' || *c == '&' || *c == '+' || *c == '!')

enum
{
	FD_FREE,
	FD_SERVER,
	FD_CLIENT
};

typedef struct			s_user
{
	void				*is;
	struct s_user		*prev;
	struct s_user		*next;
}						t_user;

typedef struct			s_chan
{
	char				name[CHAN_SIZE + 1];
	char				topic[TOPIC_SIZE + 1];
	int					mode;
	size_t				nbusers;
	t_user				*user;
	struct s_chan		*next;
	struct s_chan		*prev;
}						t_chan;

typedef struct			s_fd
{
	int					fd;
	struct sockaddr		csin;
	char				addr[1025];
	char				port[32];
	short				type;
	long				flags;
	time_t				time;
	char				flood;
	char				nick[NAME_SIZE + 1];
	char				*away;
	t_user				*user;
	t_chan				*chan;
	void				(*fct_read)();
	void				(*fct_write)();
	t_buf				rd;
	t_buf				wr;
	char				buf_read[BUFF + 1];
	char				buf_write[BUFF + 1];
	struct s_fd			*next;
	struct s_fd			*prev;
}						t_fd;

typedef struct			s_env
{
	char				verb;
	char				name[NAME_SIZE + 1];
	int					ipv4;
	char				addr4[16];
	int					ipv6;
	char				addr6[16];
	char				*creation;
	size_t				members;
	t_fd				*fds;
	t_chan				*chan;
	fd_set				fd_read;
	fd_set				fd_write;
}						t_env;

typedef struct			s_com
{
	char				*name;
	void				(*fct)(char **, t_env *, t_fd *);
}						t_com;

void					sv_error(char *str, t_env *e);
void					sv_init_server(char **av, t_env *e);
void					sv_accept(t_env *e, int ip);
int						sv_new_client(t_env *e, t_fd *new);
int						sv_loop(t_env *e);
void					sv_cl_prompt(t_fd *cl);
void					sv_cl_read(t_env *e, t_fd *cl);
void					sv_cl_write(t_env *e, t_fd *cl);
void					sv_cl_end(char **cmds, t_env *e, t_fd *cl);
//int						sv_flood_protect(t_env *e, int id);
void					sv_nick(char **cmds, t_env *e, t_fd *cl);
void					sv_join(char **cmds, t_env *e, t_fd *cl);
void					sv_leave(char **cmds, t_env *e, t_fd *cl);
void					sv_leave_chan(t_env *e, t_fd *cl);
void					sv_msg(char **cmds, t_env *e, t_fd *cl);
void					sv_who(char **cmds, t_env *e, t_fd *cl);
void					sv_list(char **cmds, t_env *e, t_fd *cl);
void					sv_help(char **cmds, t_env *e, t_fd *cl);
void					sv_connect(char **cmds, t_env *e, t_fd *cl);
void					sv_topic(char **cmds, t_env *e, t_fd *cl);
void					sv_away(char **cmds, t_env *e, t_fd *cl);
void					sv_sendto_chan_msg(char *msg, t_fd *cl);
void					sv_sendto_chan_new(t_fd *cl);
void					sv_sendto_chan(t_fd *cl);
char					**sv_split(t_buf *buf);
char					*sv_strchr(const t_buf *b, int c);
void					sv_err(char *nick, char *err, int fd);
t_user					*sv_add_chan_user(t_chan *chan, t_user *new);
t_user					*sv_new_user(t_fd *id);

#endif
