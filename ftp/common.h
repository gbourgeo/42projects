/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 06:46:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 09:46:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/socket.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>

# define CLIENT			1
# define SERVER			2

/*
** BUFF_SIZE :
** Size of the client/server command line.
** Low value and long command will probably lead to an obsolete interaction
** with the server.
*/

# define BUFF_SIZE		1024

/*
** DATA_SIZE :
** Mostly (but not only) used to transfert files between client and server.
** High value may result on a higher transfert speed but
** may lead on undefined behaviours depending on the system.
*/

# define DATA_SIZE		2048

/*
** CLIENTS_MAX :
** Server uses fork to work (...i know...) so
** The size may be under the limit of your system fork limit :
** see limits.conf on linux,
** or MAXUPRC in <sys/param.h> under OSX (usually 266).
*/

# define CLIENTS_MAX	20

typedef struct			s_envi
{
	int					ip[2];
	int					fd;
	int					rec;
	int					success;
	char				buff[BUFF_SIZE + 1];
	char				data[DATA_SIZE + 1];
	char				*user;
	char				*path;
	char				*home;
	char				*pwd;
	char				*lpwd;
	char				*oldpwd;
	struct stat			info;
	pid_t				pid;
}						t_envi;

int						usage(char *prog_name, int caller);
void					ft_error(const char *err);
char					*ft_getenv(char *search, char **envp);
char					**ft_split_whitespaces(char *str);
char					*ft_strndup(const char *s1, int size);
char					*ft_get_path(char *dest, char *home, char *lpwd, \
										char *oldpwd);
int						file_error(char *msg, t_envi *e, int caller, int fd);
void					ft_putendn(int nb);
void					ft_free(char ***tab);
void					ft_signals(void);

#endif
