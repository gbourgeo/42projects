/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 16:09:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/27 16:17:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "all.h"

/*
**	Options structure
*/
typedef struct	s_options
{
	const char	*sname;
	const char	*fname;
	const char	*argument;
	const char	*description;
	void		(*handler)(char *, t_params *);
}				t_options;

t_options		*nmap_options(int getsize);

/*
**	PARAMETERS
*/
void			get_file_parameters(char *arg, t_params *e);
void 			get_ip_parameters(char *arg, t_params *e);
void			get_ports_parameters(char *arg, t_params *e);
void 			get_scans_parameters(char *arg, t_params *e);
void 			get_timeout_parameters(char *arg, t_params *e);
void 			get_threads_parameters(char *arg, t_params *e);
void			print_help(char *arg, t_params *e);

t_addr			**get_new_addr(char *name, t_addr **tmp, t_params *e);

typedef struct	s_scans
{
	const char	*name;
	int			value;
}				t_scans;

t_scans			*nmap_scans(int getsize);

#endif
