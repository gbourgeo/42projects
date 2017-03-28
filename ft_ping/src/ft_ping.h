/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 22:56:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/29 00:05:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdlib.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

# define OPTIONS "[-nqvh] [-c count] [-s packetsize] [-t ttl]"
# define DEFDATALEN 56

enum					e_options
{
	opt_c,
	opt_n,
	opt_q,
	opt_v,
	opt_len
};

typedef struct			s_hdr
{
	struct msghdr		msg;
	struct iovec		iov;
	struct sockaddr_in	from;
	struct cmsghdr		*cmsg;
}						t_hdr;

typedef struct			s_env
{
	char				*prog;
	char				options[opt_len];
	int					count;
	int					ttl;
	int					sock;
	char				*hostname;
	double				interval;
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
	long				nerrors;
	double				tmin;
	double				tmax;
}						t_env;

struct s_env			e;

double					ft_atod(char *str);
void					ft_init(void);
void					ft_signals(void);
void					ft_setup(void);
void					ft_finish(int sig);
void					ft_alarm(int sig);
void					ft_pinger(void);
void					ft_analyse(char *buf, int cc, struct sockaddr_in *from);

#endif
