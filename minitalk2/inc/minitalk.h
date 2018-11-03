/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:28:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/31 09:10:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netdb.h>
# include <string.h>
# include <signal.h>
# include <ncurses.h>
# include <time.h>

# define MAX_CLIENTS	10
# define NICK_CLIENTS	9
# define BUF_CLIENTS	512

typedef struct	s_opt
{
	char		*ip;
	char		*port;
	int			size;
	char 		*user;
	int			fd;
}				t_opt;

typedef struct	s_ncu
{
	WINDOW		*mainWin;
	WINDOW		*tchatWinBox;
	WINDOW		*tchatWin;
	WINDOW		*usersWinBox;
	WINDOW		*usersWin;
	WINDOW		*textWinBox;
	WINDOW		*textWin;
	WINDOW		*infoLine;
}				t_ncu;

typedef struct	s_cl
{
	int			fd;
	int			try;
	char		user[NICK_CLIENTS];
	char		rd[BUF_CLIENTS];
	char		wr[BUF_CLIENTS];
	int			leaved;
}				t_cl;

typedef struct	s_usr
{
	struct s_usr	*prev;
	char			name[NICK_CLIENTS];
	struct s_usr	*next;
}				t_usr;

typedef int	(*type1)(int, const struct sockaddr *, socklen_t);
typedef int	(*type2)(int, int);

void			ncurses_start();
void			ncurses_end();
void			termTooSmall();
void			createChatBox();
void			createUsersBox();
void			createTextBox();
void			createInfoLine();

void			add_user(char *name);
void			del_user(char *name);
void			parse_users(char *buf, int pos);
void			aff_users(t_ncu *n);
void			send_users(const char *key, t_cl *cl);
void			clear_users();

void			quitprogram(int signum);
void			changewindow(int signum);

void			wprintTime(WINDOW *win, time_t ts);

int				opensocket(char *ip, char *port, type1 func, type2 func2);
void			loop(int server, int size, char *ip, char *port);
void			clear_clients(t_cl *cl, int size);

#endif
