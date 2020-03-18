/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 06:46:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 11:24:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <signal.h>

# ifdef __linux__
#  define NSIG _NSIG
# elif
//# ifndef MSG_NOSIGNAL
#  define MSG_NOSIGNAL 0
# endif

# ifndef WCOREDUMP
#  define HAS_WCOREDUMP 0
# else
#  define HAS_WCOREDUMP 1
# endif

# define FTP_RESET		"\x1B[0m"
# define FTP_BOLD		"\x1B[1m"
# define FTP_DARK		"\x1B[2m"
# define FTP_ITALIC		"\x1B[3m"
# define FTP_UNDERLINED	"\x1B[4m"
# define FTP_RED		"\x1B[31m"
# define FTP_GREEN		"\x1B[32m"
# define FTP_YELLOW		"\x1B[33m"
# define FTP_BLUE		"\x1B[34m"
# define FTP_PINK		"\x1B[35m"
# define FTP_LIGHT_BLUE	"\x1B[36m"
# define FTP_GREY		"\x1B[37m"

# define FT_CHECK			ft_check_option

/*
** FTP_BUFF_SIZE :
** Size of the client/server command line.
** Low value and long command will probably lead to an obsolete interaction
** with the server.
*/

# define CMD_BUFF_SIZE		128

/*
** DATA_SIZE :
** Mostly (but not only) used to transfert files between client and server.
** High value may result on a higher transfert speed but
** may lead on undefined behaviours depending on the system.
*/

# define DATA_BUFF_SIZE		65536

enum
{
	IS_OK = 0,
	ERR_HELP,
	ERR_NB_PARAMS,
	ERR_WRONG_PARAM,
	ERR_INVALID_PARAM,
	ERR_DIGIT_PARAM = 5,
	ERR_TOOMUCH_PARAM,
	ERR_GETADDR,
	ERR_NO_IPV4_AVAIL,
	ERR_NO_IPV6_AVAIL,
	ERR_SETSOCKOPT = 10,
	ERR_LISTEN_V4,
	ERR_OPEN,
	ERR_LISTEN_V6,
	ERR_MALLOC,
	ERR_SELECT = 15,
	ERR_ACCEPT_V4,
	ERR_ACCEPT_V6,
	ERR_RECV,
	ERR_DISCONNECT,
	ERR_SIGNAL = 20,
	ERR_WAIT,
	ERR_FORK,
	ERR_DUP2,
	ERR_EXECV,
	ERR_SEND = 25,
	ERR_INVALID_NAMEPASS,
	ERR_CHDIR,
	ERR_COMMAND,
	ERR_REGISTERED,
	ERR_WRITE = 30,
	ERR_USER_FILE,
	ERR_GETNEXTLINE,
	ERR_CONNECT_TO,
	ERR_OPEN_PORT,
	ERR_DATA_HDR = 35,
	ERR_TIMEOUT,
	ERR_LSEEK,
	ERR_MMAP,
	ERR_FSTAT,
	ERR_NOT_REGULAR_FILE = 40,
	ERR_NO_SERVER,
	ERR_NCURSE_MAIN,
	ERR_NCURSE_TEXTBOX,
	ERR_NCURSE_TEXTWIN,
	ERR_NCURSE_LISTBOX = 45,
	ERR_NCURSE_LISTWIN,
	ERR_NCURSE_CHATBOX,
	ERR_NCURSE_CHATWIN,
	ERR_READ,
	ERR_OPEN_TTY = 50,
	ERR_TCGETATTR,
	ERR_TCSETATTR,
	ERR_QUIT,
	ERR_TERM_NOT_DEFINED,
	ERR_TERM_DATABASE = 55,
	ERR_TERM_NOT_FOUND,
	ERR_PIPE,
	ERR_ALREADY_CONNECTED,
};

typedef struct		s_env
{
	char			*path;
	char			*home;
	char			*pwd;
	char			*oldpwd;
}					t_env;

typedef struct		s_common
{
	char			*progpath;
	char			*progname;
	t_env			env;
}					t_common;

/*
** Ring-Buffer structure
*/

typedef struct		s_buff
{
	char			*head;
	char			*tail;
	char			buff[CMD_BUFF_SIZE];
	int				len;
}					t_buff;

/*
** Commands structure
*/

typedef struct		s_command
{
	const char		*name;
	const char		*descrip;
	int				(*help)();
	int				(*func)();
	int				rights;
}					t_command;

const char			*get_signal_name(int sig);
void				print_signal_info(int sig, int interactive);
int					ft_check_option(int option, int value);

int					ft_check_path(char **path, char *pwd, char *home);
void				ft_close(int *fd);
int					ft_error(int errnb, t_common *info);
char				*ft_get_command(char *cmd, char *paths, int n);
const char			*ft_get_error(int errnb);
char				*ft_getenv(char *search, char **envp);
int					ft_init(void *p, int size, char **environ, char *prog);
char				*ft_recreate_path(char *path);
char				**ft_split_whitespaces(char *str);
char				*ft_strcset(char *src, const char *charset);
char				**ft_strsplit2(char const *s, char c);
char				*ft_ringbuffcpy(char *buff, int size, t_buff *ring);
int					ftp_strcmp(const char *s1, const char *s2);

#endif
