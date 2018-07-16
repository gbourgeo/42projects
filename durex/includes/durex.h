/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:16:36 by root              #+#    #+#             */
/*   Updated: 2018/07/16 23:27:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

# define CLIENT_MAX		3
# define CLIENT_BUFF	128

/* memset strcpy */
# include <string.h>
/* select */
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define SERVER_ADDR	"localhost"
# define SERVER_PORT	"4242"
# define SERVER_COMMANDS	"help", "shell"
# define SERVER_HELP		"display this help", "spawn a shell"
# define SERVER_FUNCTIONS	&serverHelp, &serverShell

typedef struct	s_buff
{
	char		buff[CLIENT_BUFF];
	char		*head;
	char		*tail;
}				t_buff;

typedef struct	s_cl
{
	int			fd;
	int			logged;
	t_buff		rd;
	t_buff		wr;
}				t_cl;

typedef struct	s_sv
{
	int			fd;
	fd_set		fdr;
	fd_set		fdw;
	t_cl		client[CLIENT_MAX];
}				t_sv;

int				openServer(const char *addr, const char *port);
void			serverAcceptConnections(t_sv *server);
void			serverReadClient(t_cl *client);
void			serverWriteClient(t_cl *client);
void			serverHelp(t_cl *client);
void			serverShell(t_cl *client);
void			quitServer(t_sv *server);
void			clearClient(t_cl *client);

void			clientRead(char *buff, int size, t_cl *client);
void			clientWrite(char *str, t_cl *client);

void			encrypt(char *msg, size_t size);

#endif /* DUREX_H */
