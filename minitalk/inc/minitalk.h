/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:28:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/29 09:46:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <string.h>
# include <signal.h>

# define MAX_CLIENTS	10

typedef struct	s_opt
{
	char		*ip;
	char		*port;
	int			size;
	char 		*user;
	int			fd;
}				t_opt;

typedef struct	s_cl
{
	int			fd;
	int			try;
	char		user[12];
	char		rd[512];
	char		wr[512];
	int			leaved;
}				t_cl;

struct s_cl		clients[MAX_CLIENTS];

typedef int	(*type1)(int, const struct sockaddr *, socklen_t);
typedef int	(*type2)(int, int);

int				opensocket(char *ip, char *port, type1 func, type2 func2);
void			loop(int server, int size);
void			clear_clients(t_cl *cl, int size);

#endif
