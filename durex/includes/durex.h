/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:16:36 by root              #+#    #+#             */
/*   Updated: 2018/07/15 05:20:56 by root             ###   ########.fr       */
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

typedef struct	s_buff
{
	
}				t_buff;

typedef struct	s_cl
{
	int			fd;
	int			logged;
	char		rd[CLIENT_BUFF];
	char		*rdHead;
	char		*rdTail;
	char		wr[CLIENT_BUFF];
	char		*wrHead;
	char		*wrTail;
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
void			quitServer(t_sv *server);
void			clearClient(t_cl *client);

void			clientWrite(char *str, t_cl *client);

#endif /* DUREX_H */
