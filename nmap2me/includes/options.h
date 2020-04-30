/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 16:09:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/04/30 12:02:32 by gbourgeo         ###   ########.fr       */
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
	char		**(*handler)(char **, t_params *);
}				t_options;

t_options		*nmap_options(int getsize);

/*
**	PARAMETERS
*/
char			**get_debug_parameters(char **arg, t_params *e);
char			**get_file_parameters(char **arg, t_params *e);
char 			**get_iflist_parameters(char **arg, t_params *e);
char			**get_interface_parameters(char **arg, t_params *e);
char 			**get_ip_parameters(char **arg, t_params *e);
char			**get_ports_parameters(char **arg, t_params *e);
char			**get_retry_parameters(char **arg, t_params *e);
char 			**get_scans_parameters(char **arg, t_params *e);
char 			**get_timeout_parameters(char **arg, t_params *e);
char 			**get_threads_parameters(char **arg, t_params *e);
char			**get_verbose_parameters(char **arg, t_params *e);
char			**get_help(char **arg, t_params *e);

t_addr			*add_new_addr(char *name, t_addr **addr);

typedef struct	s_scans
{
	const char	*name;
	int			value;
}				t_scans;

t_scans			*nmap_scans(int getsize);

#endif
