/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 06:46:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 23:46:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <signal.h>

# ifdef __linux__
#  define NSIG _NSIG
# endif

# define COLOR_RESET		"\x1B[0m"
# define COLOR_BOLD			"\x1B[1m"
# define COLOR_DARK			"\x1B[2m"
# define COLOR_ITALIC		"\x1B[3m"
# define COLOR_UNDERLINED	"\x1B[4m"
# define COLOR_RED			"\x1B[31m"
# define COLOR_GREEN		"\x1B[32m"
# define COLOR_YELLOW		"\x1B[33m"
# define COLOR_BLUE			"\x1B[34m"
# define COLOR_PINK			"\x1B[35m"
# define COLOR_LIGHT_BLUE	"\x1B[36m"
# define COLOR_GREY			"\x1B[37m"

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

# define DATA_BUFF_SIZE		2048

# define ERR_OUTPUT	"\x0f\xff>ERROR\n"
# define OK_OUTPUT	"\x0f\x01>SUCCESS\n"

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
	ERR_TRANSFERT,
	ERR_OPEN_PORT,
	ERR_DATA_HDR = 35,
	ERR_TIMEOUT,
	ERR_LSEEK,
	ERR_MMAP,
	ERR_FSTAT,
	ERR_NOT_REGULAR_FILE = 40,
	ERR_NO_SERVER,
};

typedef struct		s_env
{
	char			*path;
	char			*home;
}					t_env;

typedef struct		s_common
{
	char			*progpath;
	char			*progname;
	t_env			env;
}					t_common;

void				print_signal_info(int sig, int interactive);
int					ft_check_option(int option, int value);

int					ft_init(void *p, int size, char **environ, char *prog);
const char			*ft_get_error(int errnb);
int					ft_error(int errnb, t_common *info);
char				*ft_getenv(char *search, char **envp);
char				**ft_split_whitespaces(char *str);
char				*ft_strcset(char *src, const char *charset);
char				**ft_strsplit2(char const *s, char c);
void				ft_close(int *fd);

char				*ft_strndup(const char *s1, int size);
char				*ft_get_path(char *dest, char *home, char *lpwd,
					char *oldpwd);
char				*ft_get_command(char *cmd, char *paths, int n);
void				ft_putendn(int nb);
void				ft_signals(void);
void				ft_freetab2(char ***tab, int freeall);

#endif
