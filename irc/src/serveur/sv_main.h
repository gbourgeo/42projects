/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:43:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include "common.h"
# include "help.h"
# include "err_list.h"
# include "commands.h"
# include "flags.h"
# include "conf.h"
# include <netinet/in.h>
# include <netdb.h>

/*
** Negative value of any of this defines will lead to unexpected behaviors !!!
*/

# define PORT_LEN 5
# define SID_LEN 4

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
# define SERVER_LEN	1025

/*
** CHAN_LIMIT		The maximum number of channels a client can join.
*/
# define CHAN_LIMIT	120

/*
** CHANNAME_LEN		The maximum length a channels' name can be. Over this value,
**					a channel name will be truncated.
*/
# define CHANNAME_LEN 50

/*
** CHANKEY_LEN		THe maximum length a channel key can be.
*/
# define CHANKEY_LEN 23

/*
** TOPIC_LEN		The maximum length of a topic. Over this value, the
**					topic will be truncated.
*/
# define TOPIC_LEN	80

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

# define V4ADDR(csin) &((struct sockaddr_in *)csin)->sin_addr.s_addr
# define V6ADDR(csin) &((struct sockaddr_in6 *)csin)->sin6_addr.s6_addr

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

typedef struct			s_file
{
	char				registered;
	char				username[USERNAME_LEN + 1];
	char				*pass;
	int					umode;
	char				nick[NICK_LEN + 1];
	char				**realname;
	time_t				must_change_nick;
	struct s_file		*next;
}						t_file;

typedef struct			s_info
{
	int					fd;
	struct sockaddr		csin;
	char				addr[ADDR_LEN + 1];
	char				host[NI_MAXHOST + 1];
	char				port[NI_MAXSERV + 1];
}						t_info;

typedef struct			s_fd
{
	struct s_fd			*prev;
	t_info				i;
	char				uid[10];
	t_file				*inf;
	short				type;
	char				*away;
	t_listin			*chans;
	int					chansnb;
	void				(*fct_read)();
	void				(*fct_write)();
	t_buf				rd;
	t_buf				wr;
	char				buf_read[BUFF + 1];
	char				buf_write[BUFF + 1];
	char				*queue;
	int					leaved;
	char				*reason;
	struct s_fd			*next;
}						t_fd;

typedef struct			s_chan
{
	struct s_chan		*prev;
	char				name[CHANNAME_LEN + 1];
	char				topic[TOPIC_LEN + 1];
	int					cmode;
	int					nbusers;
	int					invisibl;
	int					limit;
	char				key[CHANKEY_LEN];
	t_listin			*users;
	struct s_chan		*next;
}						t_chan;

typedef struct			s_env
{
	char				verb;
	t_conf				conf;
	char				name[SERVER_LEN + 1];
	char				addr[ADDR_LEN + 1];
	char				port[PORT_LEN + 1];
	char				sid[SID_LEN + 1];
	t_info				v4;
	t_info				v6;
	char				*creation;
	t_file				*users;
	size_t				members;
	char				userid[10];
	t_fd				*fds;
	t_chan				*chans;
	fd_set				fd_read;
	fd_set				fd_write;
	char				*ptr;
}						t_env;

typedef struct			s_grp
{
	t_listin			*list;
	char				*ptr;
	char				mdr[2];
	char				c;
	t_fd				*from;
	t_chan				*on;
	t_fd				*to;
}						t_grp;

struct s_env			e;

void					get_conf_file(t_env *e);
int						is_chan_member(t_chan *ch, t_fd *cl);
int						is_modo(t_chan *chan, t_fd *cl);
t_chan					*find_chan(char *name, t_chan *chans);
void					rpl_away(t_fd *to, t_fd *cl, t_env *e);
void					rpl_cmode(t_grp *grp, char *limit);
void					rpl_umode(t_grp *g, t_chan *c, t_fd *to, t_fd *cl);
void					rpl_motd(t_fd *cl, t_env *e);
void					send_joinmsg_toothers(t_chan *chan, t_fd *cl);
void					sv_accept(t_env *e, int ip);
t_listin				*sv_add_chantouser(t_chan *chan, t_fd *cl);
t_listin				*sv_add_usertochan(t_fd *cl, t_chan *chan);
t_user					*sv_allowed(t_info *inf, t_user *ptr);
void					sv_away(char **cmds, t_env *e, t_fd *cl);
void					sv_channel_mode(char **cmds, t_chan *ch, t_fd *cl);
void					sv_chan_user_mode(t_grp *grp, char ***cmd);
void					sv_check_clients(t_env *e);
int						sv_check_name_valid(char *name);
void					sv_cl_read(t_env *e, t_fd *cl);
void					sv_cl_send(t_fd *cl);
void					sv_cl_write(char *str, t_fd *cl);
t_fd					*sv_clear_client(t_env *e, t_fd *cl);
void					sv_connect(char **cmds, t_env *e, t_fd *cl);
int						sv_connect_client(t_fd *cl, t_env *e);
void					sv_err(char *err, char *cmd, char *cmd2, t_fd *cl);
void					sv_error(char *str, t_env *e);

void					sv_find_userinchan(char **cmd, t_chan *chan, t_fd *cl);
void					sv_get_cl_password(t_fd *cl, t_env *e);
int						sv_globcmp(const char *s1, const char *s2);
void					sv_help(char **cmds, t_env *e, t_fd *cl);
void					sv_init_server(t_env *e);
void					sv_join(char **cmds, t_env *e, t_fd *cl);
void					sv_join_chan(char *name, char ***c, t_fd *cl, t_env *e);
void					sv_leave(char **cmds, t_env *e, t_fd *cl);
void					sv_list(char **cmds, t_env *e, t_fd *cl);
int						sv_loop(t_env *e);
void					sv_mode(char **cmds, t_env *e, t_fd *cl);
void					sv_msg(char **cmds, t_env *e, t_fd *cl);
void					sv_msg_chan(char *chan_name, char **cmds, t_fd *cl);
void					sv_new_client(t_info *info);
void					sv_nick(char **cmds, t_env *e, t_fd *cl);
void					sv_nick_change(t_fd *cl, t_env *e);
void					sv_notice(char *str, t_fd *cl);
void					sv_oper(char **cmds, t_env *e, t_fd *cl);
void					sv_pass(char **cmds, t_env *e, t_fd *cl);
void					sv_quit(char **cmds, t_env *e, t_fd *cl);
void					sv_signals(void);
void					sv_sendto_chan(t_chan *chan, t_fd *cl, t_env *e);
void					sv_sendto_chan_msg(char *msg, t_fd *cl);
void					sv_sendto_chan_new(t_fd *cl);
char					**sv_split(t_buf *buf);
char					*sv_strchr(const char *str, int c);
int						sv_tabcmp(char **t1, char **t2);
void					sv_topic(char **cmds, t_env *e, t_fd *cl);
void					sv_user(char **cmds, t_env *e, t_fd *cl);
void					sv_user_mode(char **cmds, t_fd *cl);
void					sv_welcome(t_env *e, t_fd *cl);
void					sv_who(char **cmds, t_env *e, t_fd *cl);
void					sv_who_chan(char **cmds, t_fd *cl, t_env *e);
void					sv_who_info(t_fd *us, t_fd *cl, t_env *e);

#endif
