/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:57:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 19:43:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# ifdef __linux
#  include <sys/types.h>
# endif
# include <term.h>
# include <stdlib.h>

# define IFS_DEFAULT	" \t\n"

# define NULLALIAS		(t_alias *)0

typedef struct	s_alias
{
	char			*key;
	char			*value;
	int				in_use;
	struct s_alias	*next;
	struct s_alias	*prev;
}				t_alias;

typedef struct	s_shell_env
{
	int				ac;
	char			**av;
	char			*progpath;
	char			*progname;
	char			**public_env;
	char			**private_env;
	t_alias			*alias_list;
	int				*ret;
	int				pid;
	struct termios	save;
	int				shell_loop;
	size_t			interactive;
	int				forked;
}				t_s_env;

void			init_shell_env(t_s_env *e, int ac, char **av, char **env);
void			free_shell_env(t_s_env *e);
void			launch_new_cmd(char **line, t_s_env *e);

#endif
