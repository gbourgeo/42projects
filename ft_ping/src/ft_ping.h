/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 22:56:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/07 22:29:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdlib.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

# define OPTIONS "vh"
# define DEFDATALEN 56
# define ERR_NULL { "", NULL }
# define ERR_1 { "Echo Reply", NULL }
# define ERR_20 { "Destination Net Unreachable", "Destination Host Unreachable"
# define ERR_21 "Destination Protocol Unreachable"
# define ERR_22 "Destination Port Unreachable"
# define ERR_23 "frag needed and DF set", "Source Route Failed"
# define ERR_24	"Destination Net Unknown", "Destination Host Unknown"
# define ERR_25	"Source Host Isolated", "Destination Net Prohibited"
# define ERR_26	"Destination Host Prohibited"
# define ERR_27	"Destination Net Unreachable for Type of Service"
# define ERR_28	"Destination Host Unreachable for Type of Service"
# define ERR_29	"Packet filtered", "Precedence Violation"
# define ERR_30 "Precedence Cutoff", NULL }
# define ERR_3 { "Source Quench", NULL }
# define ERR_40 { "Redirect Network", "Redirect Host"
# define ERR_41 "Redirect Type of Service and Network"
# define ERR_42 "Redirect Type of Service and Host", NULL }
# define ERR_5 { "Echo Request", NULL }
# define ERR_6 {"Time to live exceeded", "Frag Reassembly time exceeded", NULL}
# define ERR_7 { "Parameter problem: pointer = %u", NULL }
# define ERR_8 { "Timestamp", NULL }
# define ERR_9 { "Timestamp Reply", NULL }
# define ERR_10 { "Information Request", NULL }
# define ERR_11 { "Information Reply", NULL }
# define ERR_12 { "Address Mask Request", NULL }
# define ERR_13 { "Address Mask Reply", NULL }
# define ERR_14 { NULL }
# define ERRLIST_1 ERR_1, ERR_NULL, ERR_NULL, ERR_20, ERR_21, ERR_22, ERR_23,
# define ERRLIST_2 ERR_24, ERR_25, ERR_26, ERR_27, ERR_28, ERR_29, ERR_30,
# define ERRLIST_3 ERR_3, ERR_40, ERR_41, ERR_42, ERR_NULL, ERR_NULL, ERR_5,
# define ERRLIST_4 ERR_NULL, ERR_NULL, ERR_6, ERR_7, ERR_8, ERR_9, ERR_10,
# define ERRLIST_5 ERR_11, ERR_12, ERR_13, ERR_14
# define ERRLIST_FULL ERRLIST_1 ERRLIST_2 ERRLIST_3 ERRLIST_4 ERRLIST_5

enum					e_options
{
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

struct s_env			e;

void					ft_init(void);
void					ft_signals(void);
void					ft_setup(void);
void					ft_finish(int sig);
void					ft_alarm(int sig);
void					ft_pinger(void);
void					ft_analyse(char *buf, int cc, struct sockaddr_in *from);

#endif
