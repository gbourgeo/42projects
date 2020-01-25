/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:51:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_STRUCT_H
# define SV_STRUCT_H


typedef struct	s_response_options
{
	char		value;
	int			(*fct)();
}				t_ropt;

t_ropt			*sv_response_opt(char *msg);

/*
** Packet received for put, get, etc.:
**	size : Total size of the file
**	type : BINARY (1) or ASCII (2)
*/

typedef struct		s_hdr
{
	long			size;
	int				type;
}					t_hdr;

int					sv_receive_hdr(int fd, t_hdr *hdr);

/*
** Command MKDIR structure
*/

typedef struct		s_mkdir
{
	int				opt;
	int				i;
	char			**cmd;
}					t_mkdir;

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
	char		name;
	int			value;
	int			(*handler)();
}					t_type;

int					sv_type_ae(char *value, t_client *cl);
int					sv_type_l(char *value, t_client *cl);

# endif
