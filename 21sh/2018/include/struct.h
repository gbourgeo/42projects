/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:42:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/15 19:43:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <term.h>
# include <string.h>
# include <signal.h>

# ifdef __linux
#  define NSIG _NSIG
# endif

# define LEFT 1 << 0
# define RIGHT 1 << 1
# define UP 1 << 2
# define DOWN 1 << 3
# define WINCH 1 << 4

# define BIN 0
# define FILES 1
# define TMP 2
# define ENV 3
# define GET_TREE(x, y) x[y]

# define MAX_SHELL_LEN	8192

typedef enum	e_state
{
	COMPLETION = 1 << 0,
}				t_st;

typedef struct	s_tree
{
	int				value;
	int				max_len;
	int				tput;
	int				npsb;
	int				len;
	unsigned char	type;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*tern_next;
	struct s_tree	*prev;
}				t_tree;

typedef struct	s_select
{
	t_tree				*mln;
	struct s_select		*next;
	struct s_select		*prev;
	struct s_select		*down;
}				t_slct;

typedef struct	s_history
{
	char				*content;
	char				*tmp;
	size_t				c_size;
	struct s_history	*begin;
	struct s_history	*prev;
	struct s_history	*next;
}				t_hist;

typedef struct	s_buff
{
	char			buff[MAX_SHELL_LEN + 1];
	char			buff_tmp[MAX_SHELL_LEN + 2];
	int				quoted;
	struct s_buff	*next;
	struct s_buff	*prev;
}				t_buff;

typedef struct	s_state
{
	int				state;
	const char		*head;
	size_t			len;
	struct s_state	*next;

	char			*cmd;
	struct s_state	*prev;
}				t_state;

typedef struct	s_line
{
	int				slct_beg;
	int				slct_end;
	int				key;
	int				is_putb;
	int				shell_loop;
	struct termios	save;
	size_t			lprompt;
	size_t			index;
	size_t			len;
	size_t			nb_col;
	size_t			nb_line;
	char			tmp[10];
	char			*copy;
	char			*prompt;
	char			*path;
	char			*term;
	t_buff			*curr;
	t_buff			*beg_buff;
	t_hist			*hist;
	t_st			*e_cmpl;
	t_tree			*tree[4];
	char			***public_env;
	char			***private_env;
	sig_t			signals[NSIG];
	int				*ret;
}				t_line;

typedef struct	s_str_list
{
	char				*str;
	t_tree				*mln;
	int					state;
	struct s_str_list	*next;
	struct s_str_list	*prev;
}				t_slist;

typedef struct	s_stint
{
	char				*str;
	int					nb;
}				t_stint;

typedef struct	s_fctn
{
	char		*key;
	void		(*f)(t_line*);
}				t_fctn;

typedef struct	s_strlst
{
	char				*str;
	struct s_strlst		*prev;
	struct s_strlst		*next;
}				t_slst;

t_line			*get_struct(void);

#endif
