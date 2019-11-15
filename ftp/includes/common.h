/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 06:46:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 14:38:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define CLIENT				1
# define SERVER				2

/*
** FTP_BUFF_SIZE :
** Size of the client/server command line.
** Low value and long command will probably lead to an obsolete interaction
** with the server.
*/

# define FTP_BUFF_SIZE		1024

/*
** DATA_SIZE :
** Mostly (but not only) used to transfert files between client and server.
** High value may result on a higher transfert speed but
** may lead on undefined behaviours depending on the system.
*/

# define FTP_DATA_SIZE		2048

# define SERVER_ERR_OUTPUT	"\x0b\xff ERROR\n"
# define SERVER_OK_OUTPUT	"\x0b\x01 SUCCESS\n"

enum
{
	IS_OK,
	ERR_HELP,
	ERR_NB_PARAMS,
	ERR_WRONG_PARAM,
	ERR_INVALID_PARAM,
	ERR_DIGIT_PARAM,
	ERR_TOOMUCH_PARAM,
	ERR_GETADDR,
	ERR_NO_IPV4_AVAIL,
	ERR_NO_IPV6_AVAIL,
	ERR_SETSOCKOPT,
	ERR_LISTEN_V4,
	ERR_OPEN,
	ERR_LISTEN_V6,
	ERR_MALLOC,
	ERR_SELECT,
	ERR_ACCEPT_V4,
	ERR_ACCEPT_V6,
	ERR_RECV,
	ERR_DISCONNECT,
	ERR_SIGNAL,
	ERR_WAIT,
	ERR_FORK,
	ERR_DUP2,
	ERR_EXECV,
	ERR_SEND,
	ERR_INVALID_NAMEPASS,
	ERR_CHDIR,
	ERR_COMMAND,
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

int					ft_init(void *p, int size, char **environ, char *prog);
const char			*ft_get_error(int errnb);
int					ft_error(int errnb, t_common *info);
char				*ft_getenv(char *search, char **envp);
char				**ft_split_whitespaces(char *str);
char				*ft_strcset(char *src, const char *charset);
char				**ft_strsplit2(char const *s, char c);

char				*ft_strndup(const char *s1, int size);
char				*ft_get_path(char *dest, char *home, char *lpwd,
					char *oldpwd);
char				*ft_get_command(char *cmd, char *paths, int n);
void				ft_putendn(int nb);
void				ft_freetab(char ***tab);
void				ft_signals(void);

#endif
