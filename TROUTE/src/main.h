/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:42:00 by root              #+#    #+#             */
/*   Updated: 2016/09/28 13:45:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <netinet/ip.h>
# include <linux/udp.h>

# define DEF_DATALEN	40
# define MAX_DATALEN	65000
# define MIN_DATALEN	28
# define DEF_WAIT_SEC	5.0
# define DEF_HOPS		30
# define MAX_HOPS		255
# define DEF_PROBES		3
# define MAX_PROBES		10
# define DEF_SIM_QUERIE	16
# define DEF_SEND_SECS	0.0001
# define DEF_START_PORT	33434
# define DEF_UDP_PORT	53
# define DEF_AF			AF_INET
# define DEF_SOCKTYPE	SOCK_DGRAM
# define DEF_PROTOCOL	IPPROTO_UDP

enum					modules
{
	DEFAULT,
	UDP,
	ICMP
};

typedef struct			s_probe
{
	int					fd;
	int					done;
	int					seq;
	int					final;
	double				send_time;
	double				recv_time;
	struct sockaddr_in	res;
	char				err_str[10];
}						t_probe;

typedef struct			s_env
{
	char				*prog;
	char				*src;
	int					module;
	int					packetlen;
	int					headerlen;
	int					datalen;
	int					af;
	int					socktype;
	int					protocol;
	int					max_hops;
	int					nprobes;
	int					num_probes;
	int					first_hop;
	int					sim_probes;
	double				send_secs;
	double				wait;
	size_t				port;
	int					ident;
	struct sockaddr_in	source;
	struct sockaddr_in	dest;
	char				srcname[INET6_ADDRSTRLEN];
	char				srcip[INET6_ADDRSTRLEN];
	t_probe				*probes;
	u_char				*outpack;
	int					sendsk;
	u_char				inpack[1280];
	struct sockaddr_in	from;
	int					done;
}						t_env;

t_env					e;

void					ft_usage(void);
int						ft_options(char **av);
void					ft_getaddr(void);
double					ft_atod(char *str);
void					ft_init_udp(void);
void					ft_init_icmp(void);
void					ft_loop(void);
void					ft_send_udp(t_probe *pb, int ttl);
void					ft_send_icmp(t_probe *pb, int ttl);
void					ft_recv_udp(fd_set *fds);
void					ft_recv_icmp(fd_set *fds);
void					ft_recv_udp6(fd_set *fds);
void					ft_recv_icmp6(fd_set *fds);
void					ft_err(char *msg, char *err_msg);
void					ft_parse(t_probe *pb, int cc);
void					ft_reply_err(t_probe *pb, int type, int code, int info);
void					ft_reply_err6(t_probe *pb, int type, int code, int info);
double					ft_get_time(void);
void					ft_print_probe(t_probe *pb);
void					ft_print_probe6(t_probe *pb);

#endif
