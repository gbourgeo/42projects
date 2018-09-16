/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/02 04:15:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/13 18:24:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft.h"
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFF_SIZE 5

typedef struct	s_args
{
	struct s_args	*prev;
	const char		*c;
	int				selected;
	int				current;
	int				x;
	int				y;
	struct s_args	*next;
}				t_args;

typedef struct	s_info
{
	struct termios	new_term;
	t_args			*elems;
	int				lst_col;
	int				lst_len;
	int				len;
	int				col;
	int				fd;
}				t_info;

void		ft_initialize_list(const char **av, t_info *info);
void		ft_load_new_capacities(int ret);
void		ft_define_new_term_cap(int nb);
void		ft_begin_or_end(int nb);
void		ft_signals(void);
void		run(void);

char		*ft_goto(char *cap, int x, int y);
char		*ft_tgetstr(char *t);
void		ft_term_restore(int nb);
int			ft_pchar(int nb);

void		ft_perror(const char *str);
void		ft_error(const char *str);

void		ft_del_elem(t_args *elem, t_info *info);
void		ft_del_list(t_info *info);

void		ft_exit(int status);
void		ft_retur(t_info *info);

t_info		*tgetinfo(void);

void		ft_print_args(int len);
void		ft_color(const char *s, int fd);
void		key_check(char *buf, t_info *info);

#endif
