/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:42:00 by root              #+#    #+#             */
/*   Updated: 2016/09/19 02:02:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <netinet/ip.h>
# include <netinet/ip6.h>
# include <linux/udp.h>
# include <time.h>

# define DEF_DATALEN	40
# define MAX_DATALEN	65000
# define MIN_DATALEN	28
# define DEF_WAIT_SEC	5.0
# define DEF_HOPS		30
# define MAX_HOPS		255
# define DEF_PROBES		3
# define MAX_PROBES		10
# define DEF_SIM_QUERIE	16
# define DEF_SEND_SECS	0
# define DEF_START_PORT	33434
# define DEF_UDP_PORT	53
# define DEF_AF			AF_UNSPEC
# define DEF_SOCKTYPE	SOCK_DGRAM
# define DEF_PROTOCOL	IPPROTO_UDP

enum					modules
{
	DEFAULT,
	UDP,
	ICMP
};

typedef struct			s_addr_any
{
	struct sockaddr		sa;
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;
}						t_addr_any;

typedef struct			s_probe
{
	int					fd;
	int					done;
	int					seq;
	int					final;
	double				send_time;
	double				recv_time;
	t_addr_any			res;
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
	t_addr_any			source;
	char				srcname[INET6_ADDRSTRLEN];
	char				srcip[INET6_ADDRSTRLEN];
	t_probe				*probes;
	u_char				*outpack;
	int					sendsk;
	u_char				inpack[1280];
	t_addr_any			from;
	int					done;
}						t_env;

t_env					e;

void					ft_usage(void);
int						ft_options(char **av);
void					ft_getaddr(void);
double					ft_atod(char *str);
void					*ft_taballoc(size_t nmemb, size_t size);
void					ft_init_default(void);
void					ft_init_icmp(void);
void					ft_init_udp(void);
void					ft_tune_socket(int fd);
void					ft_set_ttl(int fd, int ttl);
void					ft_recverr(int fd);
void					ft_loop(void);
void					ft_send_udp(t_probe *pb, int ttl);
void					ft_send_icmp(t_probe *pb, int ttl);
void					ft_recv_udp(fd_set *fds);
void					ft_recv_icmp(fd_set *fds);
void					ft_err(char *msg, char *err_msg);
void					ft_parse_reply(t_probe *pb, int ret);
double					ft_get_time(void);

#endif
