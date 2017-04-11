/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 05:20:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 07:04:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_H
# define CONF_H

# include <netdb.h>

# define CONF_FILE "irc.conf"
# define AVAILABLE_LINES "MIO"
# define M_LINES sv_machine_information
# define I_LINES sv_client_connection
# define O_LINES sv_operator_privilege
# define ALL_LINES M_LINES, I_LINES, O_LINES

typedef struct		s_user
{
	char			mode;
	char			hostaddr[ADDR_LEN + 1];
	char			*passwd;
	char			hostname[NI_MAXHOST + 1];
	char			nick[NICK_LEN + 1];
	char			port[6];
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
