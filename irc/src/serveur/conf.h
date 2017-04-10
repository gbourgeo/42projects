/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 05:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/10 07:13:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_H
# define CONF_H

# include <netdb.h>

# define CONF_FILE "irc.conf"
# define AVAILABLE_LINES "MYIO"
# define M_LINES sv_machine_information
# define Y_LINES sv_connection_class
# define I_LINES sv_client_connection
# define O_LINES sv_operator_privilege
# define ALL_LINES M_LINES, Y_LINES, I_LINES, O_LINES

typedef struct		s_user
{
	char			mode;
	char			hostaddr[ADDR_LEN + 1];
	char			*passwd;
	char			hostname[NI_MAXHOST + 1];
	char			nick[NICK_LEN + 1];
	int				class;
	struct s_user	*next;
}					t_user;

typedef struct		s_conf
{
	t_user			*allowed_user;
	t_user			*pass_user;
	t_user			*opers;
}					t_conf;

#endif
