/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 18:34:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "shell_env.h"
# include "parser.h"

# define RET_CHUNK		10

/*
** Structure for expansions values
*/
# define NULLRET		(t_ret *)0

typedef struct	s_ret
{
	char			*word;
	size_t			w_len;
	size_t			w_max;
	const char		*head;
	size_t			i;
	int				brace;
	int				hash;
	char			*substitute;
	int				freeable;
	int				action;
	struct s_ret	*next;
}				t_ret;

/*
** Structure for expansions variables
*/
typedef struct	s_expansion
{
	t_s_env		*e;
	const char	*buff;
	size_t		buff_len;
	size_t		i;
	t_quote		*quote;
	int			expand;
}				t_exp;

int				expand_argument(t_argument *arg, t_s_env *e, int expand);
int				expand_loop(t_ret *ret, t_exp *param, int (*end_loop)(t_exp *));
int				expand_error(int error, t_ret *ret, t_exp *par, t_s_env *e);
int				expand_end(t_ret *ret, t_argument *arg);

int				expand_fieldsplit(t_ret **ret, t_s_env *e);

int				param_addchar(char c, t_ret *ret);
int				param_addstr(const char *str, t_ret *ret);

void			expand_free_t_ret(t_ret *ret, int free_ret);

int				expand_arithmetic(t_exp *param, t_ret *ret);
int				expand_subshell(t_exp *param, t_ret *ret);
int				expand_subshell_father(int pfd[2], pid_t pid, t_ret *ret);

void			debug_expansion(char *name, t_ret *ret);

#endif
