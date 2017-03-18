/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/18 03:45:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include "common.h"
# include "help.h"
# include "err_list.h"
# include "commands.h"
# include "flags.h"
# include <netinet/in.h>

/*
** Neagative value of any of this defines will lead to unexpected errors !!!
*/

/*
** LOCK_SERVER		If the value is different of 0 the server will ask for login
**					and password to each new connection.
*/
# define LOCK_SERVER 0
# define USERS_FILE ".irc_users"

/*
** MAX_CLIENT		Set the number of clients this program will handle. It can't
**					be over the system limit. (see RLIMIT_NOFILE)
*/
# define MAX_CLIENT 42

/*
** MAX_CLIENT_BY_IP Let you choose how many times a same IP can connect.
*/
# define MAX_CLIENT_BY_IP 3

/*
** USERNAME_LEN		Maximum length a client username.
*/
# define USERNAME_LEN 9

/*
** SERV_SIZE		The maximum length a servers' name can be. Over this value,
**					a server name will be truncated.
*/
# define SERVER_LEN	63

/*
** CHAN_LIMIT		The maximum number of channels a client can join.
*/
# define CHAN_LIMIT	120

/*
** CHAN_LEN			The maximum length a channels' name can be. Over this value,
**					a channel name will be truncated.
*/
# define CHAN_LEN	50

/*
** TOPIC_LEN		The maximum length of a topic. Over this value, the
**					topic will be truncated.
*/
# define TOPIC_LEN	80

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
** Some knowledge:
** - Channels with '&' as prefix are local to the server where they are created.
** - Channels with '+' as prefix do not support channel modes.  This means
**   that all the modes are unset, with the exception of the 't' channel
**   flag which is set.
** - A user who creates a channel with the character '!' as prefix is
**   identified as the "channel creator".
** - Two groups of channels: standard channels which prefix is either '&', '#'
**   or '+', and "safe channels" which prefix is '!'.
*/
# define ISCHAN(c) (c == '#' || c == '+' || c == '&' || c == '!')

enum
{
	FD_FREE,
	FD_SERVER,
	FD_CLIENT
};

/*
** I had set a void * in the struct s_listin, why?
** Because in s_fd, that void * is a t_chan *
** and in t_chan, that void * is a t_fd *
*/

typedef struct			s_listin
{
	struct s_listin		*prev;
	void				*is;
	int					mode;
	struct s_listin		*next;
}						t_listin;

typedef struct			s_reg
{
	int					registered;
	char				nick[NICK_LEN + 1];
	char				username[USERNAME_LEN + 1];
	int					umode;
	char				*password;
	char				**realname;
}						t_reg;

typedef struct			s_fd
{
	struct s_fd			*prev;
	int					fd;
	struct sockaddr		csin;
	char				addr[ADDR_LEN + 1];
	char				port[32];
	t_reg				reg;
	short				type;
	long				flags;
	time_t				time;
	char				flood;
	char				*away;
	t_listin			*chans;
	void				(*fct_read)();
	void				(*fct_write)();
	t_buf				rd;
	t_buf				wr;
	char				buf_read[BUFF + 1];
	char				buf_write[BUFF + 1];
	int					leaved;
	char				*reason;
	struct s_fd			*next;
}						t_fd;

typedef struct			s_chan
{
	struct s_chan		*prev;
	char				name[CHAN_LEN + 1];
	char				topic[TOPIC_LEN + 1];
	int					cmode;
	size_t				nbusers;
	t_listin			*users;
	struct s_chan		*next;
}						t_chan;

typedef struct			s_file
{
	char				username[USERNAME_LEN + 1];
	char				*password;
	int					mode;
	char				nick[NICK_LEN + 1];
	char				**realname;
	struct s_file		*next;
}						t_file;

typedef struct			s_env
{
	char				verb;
	int					fd;
	t_file				*users;
	char				name[SERVER_LEN + 1];
	int					ipv4;
	char				addr4[16];
	int					ipv6;
	char				addr6[16];
	char				*port;
	char				*creation;
	size_t				members;
	t_fd				*fds;
	t_chan				*chans;
	fd_set				fd_read;
	fd_set				fd_write;
	char				*ptr;
}						t_env;

typedef struct			s_com
{
	char				*name;
	void				(*fct)(char **, t_env *, t_fd *);
}						t_com;

struct s_env			e;

t_file					*get_users_list(t_env *e);
t_file					*add_in_users(t_file *users, t_fd *cl);
void					add_in_userslist(t_file *users, t_fd *cl);
void					sv_accept(t_env *e, int ip);
t_listin				*sv_add_chantouser(t_chan *chan, t_fd *cl);
t_listin				*sv_add_usertochan(t_fd *cl, t_chan *chan);
void					sv_away(char **cmds, t_env *e, t_fd *cl);
void					sv_check_clients(t_env *e);
int						sv_check_name_valid(char *name);
void					sv_cl_read(t_env *e, t_fd *cl);
void					sv_cl_write(t_env *e, t_fd *cl);
t_fd					*sv_clear_client(t_env *e, t_fd *cl);
void					sv_connect(char **cmds, t_env *e, t_fd *cl);
int						sv_connect_client(t_fd *cl, t_env *e);
void					sv_err(char *err, char *cmd, char *cmd2, t_fd *cl);
void					sv_error(char *str, t_env *e);

/*
** int						sv_flood_protect(t_env *e, int id);
*/
void					sv_get_cl_password(t_fd *cl, t_env *e);
void					sv_help(char **cmds, t_env *e, t_fd *cl);
void					sv_init_server(t_env *e);
void					sv_join(char **cmds, t_env *e, t_fd *cl);
int						sv_join_channel(char *chan_name, t_fd *cl, t_env *e);
void					sv_leave(char **cmds, t_env *e, t_fd *cl);
void					sv_list(char **cmds, t_env *e, t_fd *cl);
int						sv_loop(t_env *e);
void					sv_msg(char **cmds, t_env *e, t_fd *cl);
void					sv_new_client(int fd, struct sockaddr *csin, t_env *e);
void					sv_nick(char **cmds, t_env *e, t_fd *cl);
void					sv_notice(int fd, char *str, t_env *e);
void					sv_pass(char **cmds, t_env *e, t_fd *cl);
void					sv_quit(char **cmds, t_env *e, t_fd *cl);
void					sv_server_killed(int sig);
void					sv_sendto_chan(t_chan *chan, t_fd *cl, t_env *e);
void					sv_sendto_chan_msg(char *msg, t_fd *cl);
void					sv_sendto_chan_new(t_fd *cl);
char					**sv_split(t_buf *buf);
char					*sv_strchr(const t_buf *b, int c);
void					sv_topic(char **cmds, t_env *e, t_fd *cl);
void					sv_user(char **cmds, t_env *e, t_fd *cl);
void					sv_welcome(t_env *e, t_fd *cl);
void					sv_who(char **cmds, t_env *e, t_fd *cl);
void					update_users_file(t_env *e);

#endif
