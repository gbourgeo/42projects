/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 22:33:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 08:20:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/stat.h>

# define OPTIONS "aqk"

enum				e_options
{
	opt_a,
	opt_q,
	opt_k,
	opt_len
};

typedef struct		s_env
{
	char			*prog;
	char			**environ;
	char			opt[opt_len];
	char			*shell;
	char			*file;
	int				fd;
	int				oflag;
	struct timeval	time;
	char			**cmd;
	struct termios	term;
}					t_env;

int					ft_error(int aff_file, char *mess, t_env *e);
int					ft_start_script(t_env *e);
int					ft_fork(t_env *e);
int					ft_execve(t_env *e, int fd_m, int fd_s);
int					ft_restore_term_attr(t_env *e);
int					ft_new_term_attr(t_env *e);
char				*ft_get_path_from(char *path, t_env *e);
char				**ft_copy_env(char **environ, char *file_name, int i);
void				ft_free_env(t_env *e);

#endif
