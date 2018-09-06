/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 05:05:44 by pc                #+#    #+#             */
/*   Updated: 2018/09/05 09:32:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <sys/ioctl.h>

# define LS_OPTIONS "AFRSTUacdfgloprstu1"
# define MONTH_FR "jan ", "fév ", "mar ", "avr ", "mai ", "jui ", "jul ", \
		"aoû ", "sep ", "oct ", "nov ", "déc "
# define MONTH_US "Jan ", "Feb ", "Mar ", "Apr ", "May ", "Jun ", "Jul ", \
		"Aug ", "Sep ", "Oct ", "Nov ", "Dec "
# define BLANCS "                                                              "

typedef struct		s_inf
{
	char			permit[12];
	size_t			link;
	char			*pw_name;
	char			*gr_name;
	char			*size;
	char			*size2;
	char			date[20];
	char			*s_link;
}					t_inf;

typedef struct		s_file
{
	char			*name;
	unsigned char	type;
	struct stat		inf;
	struct s_file	*next;
	struct s_file	*prev;
	time_t			time;
	t_inf			info;
	int				len;
}					t_file;

typedef struct		s_dir
{
	char			*name;
	t_file			*file;
	int				opt[6];
	struct stat		inf;
	unsigned long	d_size;
	size_t			f_nbr;
	size_t			f_maxlen;
	int				error;
	struct s_dir	*next;
	struct s_dir	*prev;
}					t_dir;

typedef struct		s_opt
{
	char			big_a;
	char			big_f;
	char			big_r;
	char			big_s;
	char			big_t;
	char			big_u;
	char			a;
	char			c;
	char			d;
	char			f;
	char			g;
	char			l;
	char			o;
	char			p;
	char			r;
	char			s;
	char			t;
	char			u;
	char			one;
	char			date;
	t_dir			files;
	t_dir			*dir;
	int				nb_dir;
	int				ret;
	struct winsize	sz;
}					t_opt;

int					ft_perror(const char *name, t_dir *dir);
int					ft_ls_error(const char *msg, const char c);
int					ft_get_dir(char *dir_name, t_opt *options);
t_dir				*ft_create_dir(struct stat *buf, char *dir_name, t_opt *opt);
t_file				*ft_is_a_file(char *dir_name);
void				ft_ls_t(t_dir *dir);
void				ft_print_files(t_dir *dir, t_opt *opt);
void				ft_list_files(t_opt *options);
void				ft_print_dir(int ac, t_opt *options);
void				ft_print_big_f(t_file *tmp);
void				ft_ls_big_r(t_dir *dir, t_opt *options);
void				ft_ls_l(t_file *file, t_dir *dir, char *path, t_opt *opt);
void				ft_print_long_listing(t_dir *dir, t_opt *options);
void				ft_file_type(mode_t mode, t_file *file, char *path);
void				ft_owner(int *opt, t_file *file, t_opt *options);
int					ft_ls_strcmp(char *s1, char*s2);
void				ft_clear_opt(t_opt *opts);
void				ft_clear_dir(t_dir *dir);
void				ft_clear_file(t_file *file);
void				ft_sort_by_name(t_file **file);
void				ft_sort(t_opt *opt);
void				ft_sort_by_file_creation(t_opt *opt);
void				ft_sort_by_last_modif(t_opt *opt);
void				ft_sort_by_last_change(t_opt *opt);
void				ft_sort_by_last_access(t_opt *opt);
void				ft_sort_by_file_size(t_opt *opt);
void				ft_clear_opt_files(t_file **file, int l);
void				ft_clear_dir_files(t_dir **dir, int l);
void				ft_exit(char c);
void				ft_calc_date(time_t future, t_file *file, t_opt *opt);

#endif
