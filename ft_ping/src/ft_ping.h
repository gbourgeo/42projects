/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 22:56:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/24 16:43:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdlib.h>
# include <netinet/in.h>
# include <netinet/ip.h>

# define OPTIONS "vh"
# define DEFDATALEN		56

enum					e_options
{
	opt_v,
	opt_len
};

typedef struct			s_env
{
	char				*prog;
	char				options[opt_len];
	int					sock;
	char				*hostname;
	int					interval;
	int					datalen;
	int					ident;
	char				srcname[255];
	char				srcip[INET_ADDRSTRLEN];
	struct sockaddr_in	source;
	struct timeval		start;
	struct timeval		start_time;
	struct timeval		end_time;
	u_char				*outpack;
	u_char				outpackhdr[IP_MAXPACKET];
	u_char				inpack[IP_MAXPACKET];
	char				ctrl[CMSG_SPACE(sizeof(struct timeval))];
	long				ntransmitted;
	long				nreceived;
	double				tmin;
	double				tmax;
}						t_env;

t_env					e;

void					ft_init(void);
void					ft_signals(void);
void					ft_setup(void);
void					ft_finish(int sig);
void					ft_alarm(int sig);
void					ft_pinger(void);
void					ft_analyse(char *buf, int cc, struct sockaddr_in *from);

#endif
