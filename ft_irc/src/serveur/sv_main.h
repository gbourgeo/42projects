/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 12:07:06 by gbourgeo         ###   ########.fr       */
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
** Here are the defined Messages displayed in help <command>
*/

# define AWAY_1 "Mark yourself as being away. <message> is a message that will"
# define AWAY_2	" be\nautomatically sent to anyone who tries sending you a "
# define AWAY_3	"private message.\nIf you are already marked as being away, "
# define AWAY_4	"AWAY will change your status\nback to \"here\"."
# define AWAY_MSG AWAY_1 AWAY_2 AWAY_3 AWAY_4
# define CONNECT_1 "Request the server to establish a connection to <host>.\n"
# define CONNECT_2 "It is only available to FT_IRC Operators. ^^"
# define CONNECT_MSG CONNECT_1 CONNECT_2
# define HELP_1 "HELP without parameters lists all IRC commands.\n"
# define HELP_2 "HELP with a command name prints info about that command"
# define HELP_MSG HELP_1 HELP_2
# define JOIN_MSG "JOIN a new channel."
# define LEAVE_MSG "LEAVE the current channel."
# define LIST_MSG "Lists all active channels and, if set, their topics."
# define MSG_MSG "Send a private message."
# define NICK_1 "Change your nickname. You can't choose a nickname already in "
# define NICK_2 "use.\nPlus, some characters are forbiden."
# define NICK_MSG NICK_1 NICK_2
# define PASS_MSG "Set a 'connection password'."
# define QUIT_MSG "Exit from FT_IRC."
# define TOPIC_MSG "Sets the topic for the channel you're on."
# define USER_MSG "Specify the username, mode and realname of a new user."
# define WHO_1 "Followed by a channel, lists users on that channel.\n"
# define WHO_2 "WHO * lists users on the same channel as you."
# define WHO_MSG WHO_1 WHO_2

# define SV_HELPMSG1 AWAY_MSG, CONNECT_MSG, HELP_MSG, JOIN_MSG, LEAVE_MSG
# define SV_HELPMSG2 LIST_MSG, MSG_MSG, NICK_MSG, PASS_MSG, QUIT_MSG, USER_MSG
# define SV_HELPMSG3 TOPIC_MSG, WHO_MSG

# define SV_COMMANDS1 AWAY, CONNECT, HELP, JOIN, LEAVE, LIST, MSG, NICK, PASS
# define SV_COMMANDS2 QUIT, USER, TOPIC, WHO, END

# define COMMANDS1 "AWAY", "CONNECT", "HELP", "JOIN", "LEAVE", "LIST", "MSG"
# define COMMANDS2 "NICK", "PASS", "QUIT", "USER", "TOPIC", "WHO", NULL

# define SYNTAX1 "[<message>]", "<_host_> [<port>]", "[<command>]", "<channel>"
# define SYNTAX2 "<channel>", "", "<nick> <message>", "<nick>", "<password>"
# define SYNTAX3 "[<comment>]", "<user> <mode> <unused> <realname>"
# define SYNTAX4 "<channel> [<topic>]", "<channel|user>", NULL

/*
** Here i regroup all commands the server will handle and their associated
** functions.
*/
# define AWAY		{ "AWAY", sv_away }
# define CONNECT	{ "CONNECT", sv_connect }
# define HELP		{ "HELP", sv_help }
# define JOIN		{ "JOIN", sv_join }
# define LEAVE		{ "LEAVE", sv_leave }
# define LIST		{ "LIST", sv_list }
# define MSG		{ "MSG", sv_msg }
# define NICK		{ "NICK", sv_nick }
# define PASS		{ "PASS", sv_pass }
# define QUIT		{ "QUIT", sv_cl_end }
# define USER		{ "USER", sv_user }
# define TOPIC		{ "TOPIC", sv_topic }
# define WHO		{ "WHO", sv_who }
# define END		{ NULL, sv_null }

/*
** Errors list
*/
# define ERR_NOSUCHNICK	"401"
# define ERR_NOSUCHSERVER "402"
# define ERR_NOSUCHCHANNEL "403"
# define ERR_CANNOTSENDTOCHAN "404"
# define ERR_TOOMANYCHANNELS "405"
# define ERR_WASNOSUCHNICK "406"
# define ERR_TOOMANYTARGETS "407"
# define ERR_NOSUCHSERVICE "408"
# define ERR_NOORIGIN "409"
# define ERR_NORECIPIENT "411"
# define ERR_NOTEXTTOSEND "412"
# define ERR_NOTOPLEVEL "413"
# define ERR_WILDTOPLEVEL "414"
# define ERR_BADMASK "415"
# define ERR_UNKNOWNCOMMAND "421"
# define ERR_NOMOTD "422"
# define ERR_NOADMININFO "423"
# define ERR_FILEERROR "424"
# define ERR_NONICKNAMEGIVEN "431"
# define ERR_ERRONEUSNICKNAME "432"
# define ERR_NICKNAMEINUSE "433"
# define ERR_NICKCOLLISION "436"
# define ERR_UNAVAILABLERESOURCE "437"
# define ERR_USERNOTINCHANNEL "441"
# define ERR_NOTONCHANNEL "442"
# define ERR_USERONCHANNEL "443"
# define ERR_NOLOGIN "444"
# define ERR_SUMMONDISABLED "445"
# define ERR_USERDISABLED "446"
# define ERR_NOTREGISTERED "451"
# define ERR_NEEDMOREPARAMS "461"
# define ERR_ALREADYREGISTERED "462"
# define ERR_NOPERMFORHOST "463"
# define ERR_PASSWMISMATCH "464"
# define ERR_YOUREBANNEDCREEP "465"
# define ERR_YOUWILLBEBANNED "466"
# define ERR_KEYSET "467"
# define ERR_CHANNELISFULL "471"
# define ERR_UNKNOWNMODE "472"
# define ERR_INVITEONLYCHAN "473"
# define ERR_BANNEDFROMCHAN "474"
# define ERR_BADCHANNELKEY "475"
# define ERR_BADCHANMASK "476"
# define ERR_NOCHANMODES "477"
# define ERR_BANLISTFULL "478"
# define ERR_NOPRIVILEGES "481"
# define ERR_CHANOPRIVSNEEDED "482"
# define ERR_CANTKILLSERVER "483"
# define ERR_RESTRICTED "484"
# define ERR_UNIQOPPRIVSNEEDED "485"
# define ERR_NOOPERHOST "491"
# define ERR_UMODEUNKNOWNFLAG "501"
# define ERR_USERSDONTMATCH "502"

# define ISVALID(c) (((c) >= 'A' && (c) <= '~') || ft_isdigit(c) || (c) == '-')

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

/*
** The various modes available for channels are as follows:
**
**        O - give "channel creator" status;
**        o - give/take channel operator privilege;
**        v - give/take the voice privilege;
**
**        a - toggle the anonymous channel flag;
**        i - toggle the invite-only channel flag;
**        m - toggle the moderated channel;
**        n - toggle the no messages to channel from clients on the
**            outside;
**        q - toggle the quiet channel flag;
**        p - toggle the private channel flag;
**        s - toggle the secret channel flag;
**        r - toggle the server reop channel flag;
**        t - toggle the topic settable by channel operator only flag;
**
**        k - set/remove the channel key (password);
**        l - set/remove the user limit to channel;
**
**        b - set/remove ban mask to keep users out;
**        e - set/remove an exception mask to override a ban mask;
**        I - set/remove an invitation mask to automatically override
**            the invite-only flag;
*/

# define USER_MODES "Oov"

/*
** User flags.
*/
# define USR_CREATOR	0x0001
# define USR_CHANOP		0x0002
# define USR_VOICED		0x0004
# define USR_AWAY		0x0010
# define USR_RESTRICT	0x0020
# define IRC_OPERATOR	0x0040

# define CHAN_MODES "aimnqpsrtkl"

/*
** Channel flags.
*/
# define CHFL_ANNON		0x0001
# define CHFL_INVITE	0x0002
# define CHFL_MOD		0x0004
# define CHFL_NOMSG		0x0010
# define CHFL_QUIET		0x0020
# define CHFL_PRIV		0x0040
# define CHFL_SECRET	0x0100
# define CHFL_REOP		0x0200
# define CHFL_TOPIC		0x0400
# define CHFL_KEY		0x1000
# define CHFL_LIMIT		0x2000

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
int						sv_check_name_valid(char **cmds);
void					sv_cl_end(char **cmds, t_env *e, t_fd *cl);
void					sv_cl_read(t_env *e, t_fd *cl);
void					sv_cl_write(t_env *e, t_fd *cl);
t_fd					*sv_clear_client(t_env *e, t_fd *cl);
void					sv_connect(char **cmds, t_env *e, t_fd *cl);
int						sv_connect_client(t_fd *cl, t_env *e);
void					sv_err(char *err, char *cmd, char *cmd2, t_fd *cl, t_env *e);
void					sv_error(char *str, t_env *e);

/*
** int						sv_flood_protect(t_env *e, int id);
*/
void					sv_get_cl_password(t_fd *cl, t_env *e);
void					sv_help(char **cmds, t_env *e, t_fd *cl);
void					sv_init_server(t_env *e);
void					sv_join(char **cmds, t_env *e, t_fd *cl);
void					sv_leave(char **cmds, t_env *e, t_fd *cl);
void					sv_list(char **cmds, t_env *e, t_fd *cl);
int						sv_loop(t_env *e);
void					sv_msg(char **cmds, t_env *e, t_fd *cl);
void					sv_new_client(int fd, struct sockaddr *csin, t_env *e);
void					sv_nick(char **cmds, t_env *e, t_fd *cl);
void					sv_notice(int fd, char *str, t_env *e);
void					sv_pass(char **cmds, t_env *e, t_fd *cl);
void					sv_quit(int sig);
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
