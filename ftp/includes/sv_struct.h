/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:47:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_STRUCT_H
# define SV_STRUCT_H

/*
** Sv_response() options structure
*/

typedef struct		s_response_options
{
	char	value;
	int		(*fct)();
}					t_ropt;

t_ropt				*sv_response_opt(char *msg);

/*
** Command CDUP structure
*/

typedef struct		s_cdup
{
	char	*cmd;
	char	*arg;
	char	*null;
}					t_cdup;

/*
** Command RMDIR structure
*/

typedef struct		s_rmdir
{
	char			*cmd;
	int				err[3];
	char			**path;
	struct dirent	*file;
	char			*ptr;
	struct stat		inf;
}					t_rmdir;

void				sv_rmdir_open(t_rmdir *e, t_client *cl);

typedef struct		s_type
{
	char	name;
	int		value;
	int		(*handler)();
}					t_type;

int					sv_type_ae(char *value, t_client *cl);
int					sv_type_i(char *value, t_client *cl);
int					sv_type_l(char *value, t_client *cl);

#endif
