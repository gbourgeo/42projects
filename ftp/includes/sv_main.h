/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:18:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include <netinet/in.h>
# include <sys/stat.h>
# include "libft.h"
# include "common.h"

# define SV_USERS_FILE		".sv_users"
# define SV_GUEST_NAME		"guest"
# define CLIENTS_MAX		20

/*
** Maximum DATA size to transfert.
** Timeout for connection or transfert.
*/

# define TRANSFERT_MAX		2000000000
# define TRANSFERT_TIMEOUT	5

/*
** Enumeration for USERS registered
*/

enum
{
	us_server = (1 << 0),
	us_client = (1 << 1),
	us_new = (1 << 2),
};

/*
** Enumeration for SERVER options
*/

enum
{
	sv_v4 = 0,
	sv_v6,
	sv_interactive,
	sv_user_mode,
	sv_create_dir,
};

/*
** Enumeration for DATA type
*/

enum
{
	data_type_ascii = 0,
	data_type_ebcdic,
	data_type_image,
	data_type_byte_size,
	data_type_non_print,
	data_type_telnet,
	data_type_asa,
};

/*
** Users structure
*/

typedef struct		s_user
{
	int				type;
	int				rights;
	char			*home;
	char			*name;
	char			*pass;
	struct s_user	*next;
}					t_user;

/*
** Login structure
*/

typedef struct		s_login
{
	char			*user;
	int				logged;
	t_user			*member;
}					t_login;

/*
** Data transfert structure
*/

typedef struct		s_data
{
	int				type;
	int				byte_size;
	char			address[INET6_ADDRSTRLEN];
	char			*port;
	int				pasv_fd;
	int				socket;
	int				(*function)();
	pid_t			pid;
	char			*file;
	ssize_t			fsize;
	int				ffd;
}					t_data;

/*
** Client structure
**
** int errnb[4] is for:
** [0]: read errors
** [1]: write errors
** [2]: transfert errors
** [3]: client asked to quit
*/

typedef struct		s_client
{
	int				version;
	int				fd;
	int				errnb[5];
	int				(*fct_read)();
	int				(*fct_write)();
	t_buff			rd;
	t_buff			wr;
	char			*home;
	char			*pwd;
	char			*oldpwd;
	struct sockaddr	sockaddr;
	t_login			login;
	t_data			data;
	struct s_client	*prev;
	struct s_client	*next;
}					t_client;

/*
** Server structure (global)
*/

typedef void		(*t_sighandler)(int);

typedef struct		s_server
{
	t_common		info;
	t_sighandler	sig[NSIG];
	int				options;
	char			*port;
	int				ip[2];
	char			addr[2][INET6_ADDRSTRLEN];
	int				errnb[2];
	t_user			*users;
	t_client		*clients;
	int				connected;
}					t_server;

struct s_server		g_serv;

/*
** Server Options structure
*/

typedef struct		s_opt
{
	char			c;
	const char		*str;
	const char		*param;
	const char		*description;
	int				(*function)();
}					t_opt;

/*
** Binary parameters structure
*/

typedef struct		s_param
{
	t_opt			*opts;
	size_t			size;
	int				i;
}					t_param;

/*
** Parameters functions
*/

int					sv_get_addrinfo(t_server *sv);
t_opt				*sv_params(int getsize);
int					sv_params_get(char **av, t_server *sv);
int					sv_param_four(const char **arg, int *i, t_server *sv);
int					sv_param_six(const char **arg, int *i, t_server *sv);
int					sv_param_d(const char **arg, int *i, t_server *sv);
int					sv_param_h(const char **arg, int *i, t_server *sv);
int					sv_param_i(const char **arg, int *i, t_server *sv);
int					sv_param_p(const char **arg, int *i, t_server *sv);
int					sv_param_u(const char **arg, int *i, t_server *sv);
int					sv_user_file(t_server *sv);
int					sv_user_parse(char **data, t_server *sv);
int					sv_new_user(char **data, t_user **next, t_server *sv);
int					sv_save_user(t_user *user, t_client *cl, t_server *sv);

/*
** Server functions
*/

int					sv_check_option(int option, int value);
int					sv_new_pid(char **cmds, t_client *cl, char *opt);
int					sv_check_pid(t_client *cl, t_server *sv);
int					sv_init_sig(t_server *sv);
int					sv_server_accept(int version, t_server *sv);
int					sv_welcome(t_client *cl, t_server *sv);
void				sv_server_info(t_server *sv);
int					sv_server_loop(t_server *sv);
void				sv_server_end(t_server *sv, int sendmsg);
void				sv_server_close(int version, int sendmsg, t_server *sv);
void				sv_free_data(t_data *data);
void				sv_free_login(t_login *login, t_server *sv);
void				sv_free_env(t_env *env);
void				sv_free_user(t_user **user);
void				sv_assign_ptr(char **ptr, char *assign, char **table);
t_user				*sv_getuserbyname(t_user *users, const char *name);

/*
** Client functions
*/

char				*sv_client_home(const char *dir, t_user *us, t_server *sv);
int					sv_client_init(t_client *cl, t_server *sv);
int					sv_client_recv(t_client *cl);
int					sv_client_send(t_client *cl);
int					sv_client_write(const char *str, t_client *cl);
int					sv_client_nwrite(const char *str, int len, t_client *cl);
t_client			*sv_client_end(t_client *cl, t_server *sv);
t_client			*sv_client_timeout(t_client *cl);
int					sv_change_working_directory(char *home, char *pwd);
int					sv_check_err(int errnb[], int size);

/*
** Errors handler
*/

int					sv_recv_error(int ret);
int					sv_send_error(int errnb);

/*
** Commands getter
*/

t_command			*sv_commands(int getsize);

/*
** Acces Control Commands
** int					sv_acct(char **cmds, t_client *cl);
** int					sv_smnt(char **cmds, t_client *cl);
*/

int					sv_user(char **cmds, t_client *cl);
int					sv_pass(char **cmds, t_client *cl);
int					sv_cwd(char **cmds, t_client *cl);
int					sv_cdup(char **cmds, t_client *cl);
int					sv_rein(char **cmds, t_client *cl);
int					sv_quit(char **cmds, t_client *cl);

/*
** Transfert Parameter Commands
** int					sv_stru(char **cmds, t_client *cl);
** int					sv_mode(char **cmds, t_client *cl);
*/

int					sv_port(char **cmds, t_client *cl);
int					sv_pasv(char **cmds, t_client *cl);
int					sv_pasv_listen(char *port, t_client *cl);
int					sv_type(char **cmds, t_client *cl);

/*
** FTP Service Commands
** int					sv_appe(t_client *cl);
** int					sv_allo(t_client *cl);
** int					sv_rest(t_client *cl);
** int					sv_rnfr(t_client *cl);
** int					sv_rnto(t_client *cl);
** int					sv_abor(t_client *cl);
** int					sv_site(char **cmds, t_client *cl);
** int					sv_syst(char **cmds, t_client *cl);
** int					sv_stat(char **cmds, t_client *cl);
** int					sv_noop(char **cmds, t_client *cl);
*/

int					sv_retr(char **cmds, t_client *cl);
int					sv_stor(char **cmds, t_client *cl);
int					sv_stou(char **cmds, t_client *cl);
int					sv_dele(char **cmds, t_client *cl);
int					sv_rmd(char **cmds, t_client *cl);
int					sv_mkd(char **cmds, t_client *cl);
int					sv_pwd(char **cmds, t_client *cl);
int					sv_list(char **cmds, t_client *cl);
int					sv_nlst(char **cmds, t_client *cl);
int					sv_help(char **cmds, t_client *cl);
int					sv_nlst_exec(char *opt, char **arg, t_client *cl);
int					sv_retr_exec(char *opt, char **cmds, t_client *cl);
int					sv_stor_exec(char *opt, char **cmds, t_client *cl);

/*
** Special Commands
*/

int					sv_regt(char **cmds, t_client *cl);

/*
** Commands Help
*/

int					sv_user_help(t_command *cmd, t_client *cl);
int					sv_pass_help(t_command *cmd, t_client *cl);
int					sv_cwd_help(t_command *cmd, t_client *cl);
int					sv_cdup_help(t_command *cmd, t_client *cl);
int					sv_rein_help(t_command *cmd, t_client *cl);
int					sv_quit_help(t_command *cmd, t_client *cl);
int					sv_port_help(t_command *cmd, t_client *cl);
int					sv_pasv_help(t_command *cmd, t_client *cl);
int					sv_type_help(t_command *cmd, t_client *cl);
int					sv_retr_help(t_command *cmd, t_client *cl);
int					sv_stor_help(t_command *cmd, t_client *cl);
int					sv_stou_help(t_command *cmd, t_client *cl);
int					sv_dele_help(t_command *cmd, t_client *cl);
int					sv_rmd_help(t_command *cmd, t_client *cl);
int					sv_mkd_help(t_command *cmd, t_client *cl);
int					sv_pwd_help(t_command *cmd, t_client *cl);
int					sv_list_help(t_command *cmd, t_client *cl);
int					sv_nlst_help(t_command *cmd, t_client *cl);
int					sv_help_help(t_command *cmd, t_client *cl);
int					sv_regt_help(t_command *cmd, t_client *cl);
int					sv_print_help(t_client *cl, t_command *cmd, char *args,
					char **description);

/*
** Utils functions
*/
int					sv_validpathname(const char *s);
int					sv_validnumber(char **s, int ssize);
int					sv_connect_to(int *fd, t_client *cl);
int					sv_listen_from(t_client *cl, t_server *sv);
int					sv_response(t_client *cl, const char *msg, ...);

#endif
