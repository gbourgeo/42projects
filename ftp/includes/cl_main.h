/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:46:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 17:23:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MAIN_H
# define CL_MAIN_H

# include <signal.h>
# include <ncurses.h>
# include <sys/types.h>
# include "libft.h"
# include "common.h"

# define CL_HIST_SIZE	3
# define CL_HIST_FILE	".ftphist"

/*
** Enumeration for CLIENT options
*/

enum
{
	cl_verbose = 0,
};

/*
** Ncurses related enum
*/

enum
{
	CLIENT_DFLT_BCKGD = 1,
	CLIENT_COLOR_RED,
	CLIENT_DFLT_COLOR,
	CLIENT_TITLE_COLOR,
	CLIENT_TEXT_COLOR,
	CL_RED,
	CL_GREEN,
	CL_BLUE,
};

typedef struct		s_ncu
{
	WINDOW			*main;
	WINDOW			*chatbox;
	WINDOW			*chatwin;
	WINDOW			*slistbox;
	WINDOW			*slistwin;
	WINDOW			*clistbox;
	WINDOW			*clistwin;
	WINDOW			*textbox;
	WINDOW			*textwin;
}					t_ncu;

/*
** History structure
*/

typedef struct		s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}					t_hist;

/*
** Command to be launched at starting loop structure
*/

typedef struct		s_precmd
{
	WINDOW			*printtowin;
	char			*precode;
	char			*code;
	t_buff			wr;
	struct s_precmd	*next;
}					t_cmd;

/*
** Server related structure
*/

typedef struct		s_server
{
	char			*user;
	char			*pass;
	int				fd_ctrl;
	int				fd_data;
	int				receive_data;
	int				wait_response;
	char			*filename;
	int				filefd;
	int				ret;
	t_buff			wr;
	char			cmd[CMD_BUFF_SIZE];
	char			response[CMD_BUFF_SIZE];
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
	int				version;
	char			*port;
	char			*addr;
	t_ncu			ncu;
	WINDOW			*printtowin;
	t_server		server;
	t_cmd			*precmd;
	int				errnb[7];
	int				verbose;
	t_buff			rd;
	t_buff			wr;
	t_hist			*hist;
}					t_client;

struct s_client		g_cl;

/*
** Client functions
*/

int					cl_client_commands(t_buff *ring, t_client *cl);
int					cl_client_signals(t_client *cl);
int					cl_params_get(char **av, t_client *cl);
int					cl_param_i(char **av, int *i, t_client *cl);
int					cl_param_h(char **av, int *i, t_client *cl);
int					cl_param_n(char **av, int *i, t_client *cl);

int					cl_init(char **environ, t_env *env);
int					cl_ncurses_init(t_client *cl);
int					create_s_text(t_client *cl);
int					create_s_list(t_client *cl);
int					create_c_list(t_client *cl);
int					create_c_text(t_client *cl);

int					cl_history_init(t_client *cl);
t_hist				*cl_history_new(char *line, t_hist *hist);
t_hist				*cl_history_add(char *line, t_hist *hist);

int					cl_get_addrinfo(int *fd, char *addr, char *port,
t_client *cl);
int					cl_get_userinfo(t_server *sv, t_client *cl);
int					cl_get_username(t_server *sv, t_client *cl);
int					cl_get_userpass(t_server *sv, t_client *cl);

void				cl_client_end(t_client *cl);
void				cl_ncurses_end(t_client *cl);
t_cmd				*cl_precmd_end(t_cmd *cmd, int all, t_client *cl);
void				cl_history_end(t_hist *hist);

int					cl_client_loop(t_client *cl);
int					cl_client_pid(pid_t pid, t_client *cl);
void				cl_ncurses_copy(char *s);
int					cl_ncurses_read(t_buff *ring, t_client *cl);
int					cl_ncurses_write(t_buff *ring, t_client *cl);
void				cl_server_close_data(t_server *sv);
void				cl_server_close(t_server *sv, t_client *cl);
int					cl_server_recv_data(t_server *sv, t_client *cl);
int					cl_server_recv(t_buff *ring, int fd, t_client *cl);
int					cl_server_send_data(t_server *sv, t_client *cl);
int					cl_server_send(t_buff *ring, int fd, t_client *cl);
int					cl_server_write(const char buf[], t_server *sv, t_client *cl);

int					cl_pre_command(t_cmd **cmds, t_server *sv, t_client *cl);
t_cmd				*cl_pre_cmd_exec(t_cmd *cmds, t_server *sv, t_client *cl);
t_cmd				*cl_new_command(const char *name, WINDOW *win,
					char *codes[], t_cmd *next);

t_command			*cl_commands(int getsize);
int					cl_response(t_server *sv, t_client *cl);
char				*cl_ringbuffcat(char *buff, int size, t_buff *ring);

/*
** Commands
*/

int					cl_bslash(char **cmd, t_client *cl);
int					cl_bslash_cd(char **cmd, t_client *cl);
int					cl_cd(char *buf, char **cmd, t_client *cl);
int					cl_clear(char *buf, char **cmd, t_client *cl);
int					cl_connect(char *buf, char **cmd, t_client *cl);
int					cl_exit(char *buf, char **cmd, t_client *cl);
int					cl_get(char *buf, char **cmd, t_client *cl);
int					cl_help(char *buf, char **cmd, t_client *cl);
int					cl_help_local(char *buf, char **cmd, t_client *cl);
int					cl_ls(char *buf, char **cmd, t_client *cl);
int					cl_mkdir(char *buf, char **cmd, t_client *cl);
int					cl_nlst(char *buf, char **cmd, t_client *cl);
int					cl_pass(char *buf, char **cmd, t_client *cl);
int					cl_put(char *buf, char **cmd, t_client *cl);
int					cl_pwd(char *buf, char **cmd, t_client *cl);
int					cl_quit(char *buf, char **cmd, t_client *cl);
int					cl_refresh(char *buf, char **cmd, t_client *cl);
int					cl_rm(char *buf, char **cmd, t_client *cl);
int					cl_rmdir(char *buf, char **cmd, t_client *cl);

int					cl_bslash_help(t_command *cmd, t_client *cl);
int					cl_cd_help(t_command *cmd, t_client *cl);
int					cl_clear_help(t_command *cmd, t_client *cl);
int					cl_connect_help(t_command *cmd, t_client *cl);
int					cl_exit_help(t_command *cmd, t_client *cl);
int					cl_get_help(t_command *cmd, t_client *cl);
int					cl_help_help(t_command *cmd, t_client *cl);
int					cl_help_loc_help(t_command *cmd, t_client *cl);
int					cl_help_print(t_command *cmd, char *args, char **descri,
					t_client *cl);
int					cl_ls_help(t_command *cmd, t_client *cl);
int					cl_mkdir_help(t_command *cmd, t_client *cl);
int					cl_nlst_help(t_command *cmd, t_client *cl);
int					cl_pass_help(t_command *cmd, t_client *cl);
int					cl_put_help(t_command *cmd, t_client *cl);
int					cl_pwd_help(t_command *cmd, t_client *cl);
int					cl_quit_help(t_command *cmd, t_client *cl);
int					cl_refresh_help(t_command *cmd, t_client *cl);
int					cl_rm_help(t_command *cmd, t_client *cl);
int					cl_rmdir_help(t_command *cmd, t_client *cl);

/*
** Ncurses keys
*/

int					cl_ctrl_c(t_buff *ring, t_client *cl);
int					cl_ctrl_d(t_buff *ring, t_client *cl);
int					cl_lf(t_buff *ring, t_client *cl);
int					cl_backspace(t_buff *ring, t_client *cl);
int					cl_key_dc(t_buff *ring, t_client *cl);
int					cl_key_up(t_buff *ring, t_client *cl);
int					cl_key_down(t_buff *ring, t_client *cl);
int					cl_key_left(t_buff *ring, t_client *cl);
int					cl_key_right(t_buff *ring, t_client *cl);

/*
** Utils
*/

int					is_valid_response(char res[]);

#endif
