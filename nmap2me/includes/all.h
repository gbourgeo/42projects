/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 13:59:36 by frmarinh          #+#    #+#             */
/*   Updated: 2020/04/30 12:16:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <pthread.h>
# include <pcap/pcap.h>
# include <netinet/in.h>
# include <ifaddrs.h>
# include <linux/if_packet.h>
# include <netdb.h>
# include <netinet/ip.h>
# include <linux/tcp.h>
# include <net/if.h>

# define DEFAULT_THREADS 		1
# define NM_MAX_PORTS_SCAN 		1024
# define MAX_THREADS_NUMBER		250
# define SUPPORTED_SCANS		"SYN/NULL/FIN/XMAS/ACK/UDP"
# define DEFAULT_RETRY_NB		2
# define DEFAULT_TCP_TIMEOUT	1000
# define DEFAULT_TTL			64
# define PACKET_SIZE 			1024

# ifndef u_char
#  define u_char		unsigned char
# endif
# ifndef u_int
#  define u_int			unsigned int
# endif

typedef struct			s_addr
{
	char 				*name;
	char 				hostaddr[INET6_ADDRSTRLEN];
	struct addrinfo		*res;
	struct addrinfo		*ptr;
	int					addrnb;
	struct s_addr 		*next;
	struct s_addr 		*prev;
}						t_addr;

typedef struct			s_response
{
	char				received;
	char				open;
	char				filtered;
	char				raw[128];
}						t_response;

typedef struct			s_data
{
	t_addr				*addr;
	char				*scan;
	int					port;
	int					id;
	t_response			response;
}						t_data;

typedef struct 			s_thread
{
	pthread_t 			thread_id;
	t_data				*data;
	int					socket;
	int 				opes;
	struct sockaddr		*addr;
	pthread_mutex_t		*lock;
	int					retry_nb;
	int					retry_timeout;
}						t_thread;

typedef struct			s_ifaddr
{
	char				*name;
	char				ip[INET6_ADDRSTRLEN + 5];
	char				type[16];
	int					flag;
	struct s_ifaddr		*next;
}						t_ifaddr;

typedef struct			s_pcap
{
	pcap_if_t			*ifs; // Interface used
	struct sockaddr		*addr; // Interface AF_INET used
	char				*device;
	char				ip[INET6_ADDRSTRLEN];
}						t_pcap;

typedef struct			s_parameters
{
	char 				*progname;
	int 				*ports;
	char				**scans;
	t_addr 				*addresses;
	t_thread			**threads;
	char				*device;
	t_ifaddr			*ifaddrs;
	unsigned int		ports_nb;
	unsigned int		scans_nb;
	unsigned int		addresses_nb;
	unsigned int 		threads_nb;
	int					retry;
	int					tcp_timeout;
	int					verbose;
	int					debug;
	/* All system interfaces */
	pcap_if_t			*interfaces;
	t_pcap				pcap;
	pthread_mutex_t		socket_lock;
	t_data				*data;
	unsigned int		total_operations;
	/* Stats */
	struct timeval		start_time;
	struct timeval		end_time;
	int					packet_read;
}						t_params;

typedef struct			s_global
{
	pcap_t				*handle;
}						t_global;

/*
**	GLOBAL
*/
t_global				g_global;

/*
**	ERROR
*/
void 					nmap_error(t_params *e, char *str, ...);

/*
**	OTHER
*/
void					get_options(char **argv, t_params *e);
void					del_new_addr(t_addr **addr);
const char				*get_time(const char *format, struct timeval *t);
void					init_address_resolution(t_addr **addr, int debug);
void 					init_threads(t_params *e);
int						init_socket(unsigned char protocol);
void					init_ipv4_hdr(char raw[], struct sockaddr_in *to, u_int8_t protocol, struct sockaddr *addr);
unsigned short			checksum(unsigned short *ptr, int nbytes);
void					init_tcp_hdr(char raw[], t_data *data);
t_data					*find_data(int protocol, int id, t_params *e);

void		print_ip_hdr(struct iphdr *ip);
void		print_tcp_hdr(struct tcphdr *tcp);

/*
**	PCAP
*/
void 					init_pcap(t_addr *addr, t_params *e);
void					launch_pcap(t_params *e);
void					scan_report(t_addr *addr, t_params *e);

/*
**	PACKETS
*/
//int 					read_packet(char *buff, int buff_len);
//int 					construct_packet(t_addr *address, char *packet, int port);

/*
**	CLEAN
*/
void					free_params(t_params *e);
void					free_addresses(t_addr **addr);
void					free_threads(t_thread **thr, int thr_nb);
t_addr					*delete_address(t_addr *addr, t_addr **head);

/*
** SYN = synchronization
** ACK = acknowledged
** RST = reset
*/

/*
**	SYN: TCP request with flags = SYN
**	ANSWER_OPENED: TCP request with flags = SYN / ACK
**	ANSWER_CLOSED: TCP request with flags = RST
**	If the server responds with a SYN/ACK (synchronization acknowledged)
**	packet from a particular port, it means the port is open.
**	Then the hostile client sends an RST (reset) packet. As a result,
**	the server assumes that there has been a communications error,
**	and that the client has decided not to establish a connection
*/

/*
**	FIN: TCP request with flags = FIN.
**	ANSWER_OPENED: Empty, no return
**	ANSWER_CLOSED: TCP request with flags = RST
**	Attempts to close a connection that isn't open.
**	If no service is listening at the target port,
**	the operating system will generate an error message.
**	If a service is listening, the operating system will silently drop
**	the incoming packet. Therefore, no response indicates a listening
**	service at the port. However, since packets can be dropped accidentally
**	on the wire or by firewalls, this isn't a very effective scan.
**	many system always return RST. And then it is not possible to know if
**	the port is open or closed, for example Windows does this but not UNIX.
*/

/*
**	UDP:
**	ANSWER_OPENED: the packet is accepted, no response packet is sent.
**	ANSWER_CLOSED: ICMP packet with the appropriate error code such as Destination Unreachabl
**	The buffers for UDP packets are very limited in space which could
**	cause UDP packets that are sent too fast not to be processed by the
**	remote host. As a result of this, UDP port scanning is much slower
**	than TCP port scanning and by default probes only a small number of ports
*/

/*
**	XMAS: TCP request with flags = URG, PUSH, FIN.
**	ANSWER_OPENED: Empty, no return
**	ANSWER_CLOSED: TCP request with flags = RST, ACK
**	A firewall can block the tcp answer to pretend to be open
*/

/*
**	NULL: TCP request with flags = all flags to 0.
**	ANSWER_OPENED: Empty, no return
**	ANSWER_CLOSED: TCP request with flags = RST, ACK
**  l’envoi d’un paquet TCP sans flag n’est pas spécifié dans
**	le RFC décrivant le protocole TCP, c’est pourquoi il peut être
**	détecté plus facilement.
*/

/*
**	ACK: TCP request with flags = ACK
**	ANSWER_FILTRED: Empty, no return
**	ANSWER_UNFILTRED: TCP request with flags = RST
**	Used to know if an host is filtered
*/

#endif
