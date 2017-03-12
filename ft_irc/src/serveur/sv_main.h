/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 06:25:26 by gbourgeo         ###   ########.fr       */
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
** SERV_SIZE		The maximum lenght a servers' name can be. Over this value,
**					a server name will be truncated.
*/

# define SERVER_LEN	63

/*
** CHAN_SIZE		The maximum lenght a channels' name can be. Over this value,
**					a channel name will be truncated.
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

/*
** Here are the defined Messages displayed in help <command>
*/

# define AWAY_1 "Mark yourself as being away. <message> is a message that will"
# define AWAY_2	" be\nautomatically sent to anyone who tries sending you a "
# define AWAY_3	"private message.\nIf you are already marked as being away, "
# define AWAY_4	"/away will change your status\nback to \"here\"."
# define AWAY_MSG AWAY_1 AWAY_2 AWAY_3 AWAY_4
# define CONNECT_1 "Request the server to establish a connection to <host>.\n"
# define CONNECT_2 "It is only available to IRC Operators."
# define CONNECT_MSG CONNECT_1 CONNECT_2
# define HELP_1 "/help without parameters lists all IRC commands.\n"
# define HELP_2 "/help with a command name prints info about that command"
# define HELP_MSG HELP_1 HELP_2
# define JOIN_MSG "Leave the current channel and join a new one."
# define LEAVE_MSG "Leave the current channel."
# define LIST_MSG "Lists all active channels and, if set, their topics."
# define MSG_MSG "Send a private message."
# define NICK_1 "Change your nickname. You can't choose a nickname already in "
# define NICK_2 "use.\nPlus, some characters are forbiden."
# define NICK_MSG NICK_1 NICK_2
# define QUIT_MSG "Exit from FT_IRC."
# define TOPIC_MSG "Sets the topic for the channel you're on."
# define WHO_1 "Without parameters lists users on all channels.\n"
# define WHO_2 "Followed by a channel, lists users on that channel.\n"
# define WHO_3 "/who * lists users on the same channel as you."
# define WHO_MSG WHO_1 WHO_2 WHO_3

# define ISVALID(c) (((c) >= 'A' && (c) <= '~') || ft_isdigit(c) || (c) == '-')
# define ISCHAN(c) (c == '#' || c == '&' || c == '+' || c == '!')

enum
{
	FD_FREE,
	FD_SERVER,
	FD_CLIENT
};

/*
** I had set a void * in the struct s_user because i couldn't set it as t_fd *.
** The structures definition won't allow it. Such a mess.
*/

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

typedef struct			s_reg
{
	int					registered;
	char				login[NICK_LEN + 1];
	char				*password;
}						t_reg;

typedef struct			s_fd
{
	int					fd;
	struct sockaddr		csin;
	char				addr[1025];
	char				port[32];
	t_reg				reg;
	short				type;
	long				flags;
	time_t				time;
	char				flood;
	char				nick[NICK_LEN + 1];
	char				*away;
	t_user				*user;
	t_chan				*chan;
	void				(*fct_read)();
	void				(*fct_write)();
	t_buf				rd;
	t_buf				wr;
	char				buf_read[BUFF + 1];
	char				buf_write[BUFF + 1];
	int					leaved;
	struct s_fd			*next;
	struct s_fd			*prev;
}						t_fd;

typedef struct			s_file
{
	char				login[NICK_LEN + 1];
	char				*password;
	struct s_file		*next;
}						t_file;

typedef struct			s_env
{
	char				verb;
	t_file				*users;
	char				name[SERVER_LEN + 1];
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

struct s_env			e;

t_file					*get_users_list(void);
void					sv_accept(t_env *e, int ip);
t_user					*sv_add_chan_user(t_chan *chan, t_user *new);
void					sv_away(char **cmds, t_env *e, t_fd *cl);
int						sv_check_name_valid(char **cmds);
void					sv_cl_end(char **cmds, t_env *e, t_fd *cl);
void					sv_cl_read(t_env *e, t_fd *cl);
void					sv_cl_write(t_env *e, t_fd *cl);
t_fd					*sv_clear_client(t_env *e, t_fd *cl);
void					sv_connect(char **cmds, t_env *e, t_fd *cl);
int						sv_connect_client(t_fd *cl, t_env *e);
void					sv_err(char *nick, char *err, int fd);
void					sv_error(char *str, t_env *e);
/*
** int						sv_flood_protect(t_env *e, int id);
*/
void					sv_get_cl_password(t_fd *cl, t_env *e);
void					sv_help(char **cmds, t_env *e, t_fd *cl);
void					sv_init_server(char **av, t_env *e);
void					sv_join(char **cmds, t_env *e, t_fd *cl);
void					sv_leave(char **cmds, t_env *e, t_fd *cl);
void					sv_leave_chan(t_env *e, t_fd *cl);
void					sv_list(char **cmds, t_env *e, t_fd *cl);
int						sv_loop(t_env *e);
void					sv_msg(char **cmds, t_env *e, t_fd *cl);
void					sv_new_client(int fd, struct sockaddr *csin, t_env *e);
t_user					*sv_new_user(t_fd *id);
void					sv_nick(char **cmds, t_env *e, t_fd *cl);
void					sv_quit(int sig);
void					sv_sendto_chan(t_fd *cl);
void					sv_sendto_chan_msg(char *msg, t_fd *cl);
void					sv_sendto_chan_new(t_fd *cl);
char					**sv_split(t_buf *buf);
char					*sv_strchr(const t_buf *b, int c);
void					sv_topic(char **cmds, t_env *e, t_fd *cl);
void					sv_who(char **cmds, t_env *e, t_fd *cl);

#endif
