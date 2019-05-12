/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:24:07 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/28 18:37:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_EXPORT_H
# define BUILTIN_EXPORT_H
# include "ft_printf.h"
# include "ft_dprintf.h"

typedef struct	s_export
{
	int		opt_p;
	int		cnt_opt;
}				t_export;

t_export		*def_s_export(t_execute *exec);
int				exec_export(char *arg, t_s_env *e);
void			add_exported(char *arg, t_s_env *e);
char			**clone_arr(char **arr);
char			**clone_2_arr(char **arr1, char **arr2);
int				has_value(char *var);
int				is_local(char *var, char **private_env);
int				is_public(char *var, char **public_env);
int				is_exported(char *var, char **exported_env);
int				count_strarr(char **str_array);
void			export_print(char **exported, char **public_env);
void			export_sort(char ***sorted);
int				var_name_len(char *var);
void			add_public(char *arg, t_s_env *e);
void			change_public(char *arg, t_s_env *e);
void			delete_local(char *arg, t_s_env *e, int i, int j);
void			delete_exported(char *arg, t_s_env *e, int i, int j);
void			change_public_env(char *arg, t_s_env *e);
int				valid_id(char *arg);
int				has_invalid_id(char *arg);
int				illegal_option_export(char *opion);

#endif
