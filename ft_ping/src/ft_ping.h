/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 22:56:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/10 10:24:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdlib.h>
# include <netinet/in.h>

# define OPTIONS "vh"
# define PORT 1025
# define MAXPACKETSIZE (65536 - 60 - 8)
# define DEFDATALEN 56
# define MAXWAIT 10
enum					e_options
{
	opt_v,
	opt_len
};

typedef struct			s_env
{
	char				*prog;
	char				*hostname;
	size_t				datalen;
	int					interval;
	int					sock;
	struct sockaddr_in	source;
	char				srcname[1025];
	char				options[opt_len];
	struct timeval		start_time;
	char				outpack[MAXPACKETSIZE];
	size_t				npackets;
	size_t				ntransmitted;
	size_t				nreceived;
	long				tmin;
	long				tmax;
	u_long				tsum;
}						t_env;

t_env					e;

void					ft_init(void);
void					ft_signals(void);
void					ft_setup(void);

#endif
