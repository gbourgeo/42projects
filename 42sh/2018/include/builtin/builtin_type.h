/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:05:29 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/04 20:12:39 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_TYPE_H
# define BUILTIN_TYPE_H
# include "ft_printf.h"
# include "ft_dprintf.h"
# include <sys/stat.h>

typedef struct	s_type
{
	int	opt;
	int opt_p;
	int opt_f;
	int opt_bigp;
	int	opt_a;
	int opt_t;
	int	cnt_opt;
}				t_type;

struct stat		st;

void			get_option(char *option, t_type *type, int i);
int				illegal_option(char *option);
int				count_options(char **av);
t_type			*def_s_type(t_execute *exec);
int				exec_type(char *arg, t_type *type, t_s_env *e);
int				is_builtin(char *arg, t_type *type);
int				is_alias(char *arg, t_s_env *e, t_type *type);
int				is_keyword(char *arg, t_type *type);
int				is_file(char *arg, char **paths, t_type *type, int ret);
int				is_file_2(t_type *type, int ret, char **tmp2, char *arg);

#endif
