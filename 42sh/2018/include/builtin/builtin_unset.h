/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:29:22 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/28 19:20:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UNSET_H
# define BUILTIN_UNSET_H
# include "ft_printf.h"

int		valid_id_unset(char *arg);
void	exec_unset(char *arg, t_s_env *e);
void	exec_unset_check(char *arg, t_s_env *e);
void	delete_public(char *arg, t_s_env *e, int i, int j);
int		valid_id_unset(char *arg);
int		has_invalid_id_unset(char *arg);

#endif
