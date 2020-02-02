/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:46:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/02 04:41:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MAIN_H
# define CL_MAIN_H

# include <signal.h>
# include <ncurses.h>
# include <termios.h>
# include "libft.h"
# include "common.h"

/*
** # define COMMANDS "help", "ls", "pwd", "cd", "get", "put", "lcd", "mkdir"
** # define CMD_PLUS "rmdir", "unlink", "mget", "mput"
** # define FUNCTIONS cl_help, cl_ls_pwd, cl_ls_pwd, cl_cd, cl_get, cl_put,
** cl_lcd
** # define FUNC_PLUS cl_mkdir, cl_rmdir, cl_unlink, cl_mget_mput, cl_mget_mput
*/

/*
** Enumeration for CLIENT options
*/

enum
{
	cl_interactive = 0,
};

/*
** Ncurses related structure
*/

enum
{
	CLIENT_DFLT_BCKGD = 1,
	CLIENT_COLOR_RED,
	CLIENT_DFLT_COLOR,
	CLIENT_TITLE_COLOR,
	CLIENT_TEXT_COLOR,
	CL_WHITE,
	CL_RED,
	CL_GREEN,
	CL_BLUE,
};

typedef struct		s_ncu
{
	WINDOW			*main;
	WINDOW			*chatbox;
	WINDOW			*chatwin;
	WINDOW			*listbox;
	WINDOW			*listwin;
	WINDOW			*textbox;
	WINDOW			*textwin;
}					t_ncu;

/*
** Server related structure
*/

typedef struct		s_server
{
	int				fd_ctrl;
	int				fd_data;
	int				get_data;
	int				fd_file;
	char			*pwd;
	t_buff			rd;
	t_buff			wr;
}					t_server;

/*
** Client main structure (global)
*/

typedef void		(*t_sighandler)(int);

typedef struct		s_client
{
	t_common		info;
	t_sighandler	sig[NSIG];
	int				options;
	char			*port;
	char			*addr;
	t_ncu			ncu;
	t_server		server;
	int				errnb[4];
	char			*pwd;
	int				success;
	t_buff			rd;
	t_buff			wr;
}					t_client;

struct s_client		g_cl;

/*
** Client Binary Options Structure
*/

typedef struct		s_opt
{
	char			c;
	const char		*str;
	const char		*param;
	const char		*description;
	int				(*function)(char **, int *, t_client *);
}					t_opt;

typedef struct		s_param
{
	t_opt			*opts;
	size_t			size;
	int				i;
}					t_param;

/*
** Client Commands Structtre
*/

typedef struct		s_command
{
	const char		*name;
	int				(*func)(char **, t_client *);
}					t_command;

/*
** Client functions
*/

int					cl_client_signals(t_client *cl);
int					cl_params_get(char **av, t_client *cl);
t_opt				*cl_params(int getsize);
int					cl_param_i(char **av, int *i, t_client *cl);
int					cl_param_h(char **av, int *i, t_client *cl);
int					cl_param_n(char **av, int *i, t_client *cl);
void				cl_client_end(t_client *cl);
int					cl_get_addrinfo(t_client *cl);
int					cl_pchar(int nb);
char				*cl_tgetstr(char *t);

int					cl_ncurses_init(t_client *cl);
int					create_s_text(t_client *cl);
int					create_s_list(t_client *cl);
int					create_c_text(t_client *cl);
void				cl_ncurses_end(t_client *cl);
int					cl_client_loop(t_client *cl);
int					cl_ncurses_read(t_client *cl);
int					cl_ncurses_write(t_buff *ring, t_client *cl);
int					cl_server_recv(t_buff *ring, t_server *sv, t_client *cl);
int					cl_server_send(int fd, t_buff *ring);
int					cl_server_write(const char *buf, int size, t_server *sv);

int					cl_client_commands(t_client *cl);
t_command			*cl_commands(int getsize);

/*
** commands
*/

int					cl_help(char **cmds, t_client *cl);
int					cl_cd(char **cmds, t_client *cl);
int					cl_quit(char **cmds, t_client *cl);
int					cl_get(char **cmds, t_client *cl);
int					cl_ls(char **cmds, t_client *cl);
int					cl_mkd(char **cmds, t_client *cl);
int					cl_put(char **cmds, t_client *cl);
int					cl_pwd(char **cmds, t_client *cl);
int					cl_rm(char **cmds, t_client *cl);

#endif
