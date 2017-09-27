/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 13:59:36 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/25 19:48:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include   "../libft/includes/libft.h"
# include	<stdio.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<pthread.h>
# include	<netdb.h>
# include	<sys/socket.h>
# include	<netinet/in.h>
# include	<arpa/inet.h>
# include	<netinet/ip.h>
# include	<linux/tcp.h>
# include	<netinet/udp.h>
# include 	<unistd.h>
# include	<ifaddrs.h>
# include	<pthread.h>
# include	<pcap/pcap.h>
# include	<signal.h>

# define FLAG_SEPARATOR 	"--"
# define bool 				int
# define true 				1
# define false 				0
# define DEFAULT_THREADS 	1
# define MAX_PORTS_SCAN 	1024
# define PORTS_SIZE 		65535
# define SOCKET				int
# define SOCKET_ERROR		-1
# define BYTE				char
# define DEFAULT_TTL		64
# define PAYLOAD			""
# define DEFAULT_INTERFACE	"eth0"
# define DEFAULT_TIMEOUT	2000
# define ANSWER_BUFFER		4096
# define EXECUTION_TIME		5

typedef struct		s_flag
{
	char			*flag;
	char			*value;
	struct s_flag	*next;
}					t_flag;

/*
    96 bit (12 bytes) pseudo header needed for tcp header checksum calculation
*/
struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t length;
};

/*
**	FLAGS
*/
t_flag				*new_flag(char *flag);
t_flag				*get_flags();
void				add_flag(char *flag);
bool				add_value(char *value);
t_flag				*get_flag(char *name);

typedef struct			s_scan_type
{
	char				*name;
	struct s_scan_type	*next;
}						t_scan_type;

typedef struct		s_host
{
	char			*address;
	char			**addresses;
	struct s_host	*next;
}					t_host;

typedef struct		s_nmap
{
	t_host			*hosts;
	int				*port;
	int				ports_index;
	int				threads;
	t_scan_type		*scans;
	char			*device;
}					t_nmap;

typedef struct					s_thread_handler
{
	SOCKET						fd;
	int							start;
	int							ports_len;
	t_nmap						*nmap;
	BYTE						*buffer_raw;
	pthread_t					thread;
	struct s_thread_handler		*next;
}								t_thread_handler;

typedef struct					s_queue
{
	bool						filtered;
	bool						open;
	int							port;
	u_char						proto;
	char						*scan;
	bool						done;
	int							id;
	char						*host;
	struct s_queue				*next;
	char						*service;
}								t_queue;

typedef struct					s_global
{
	t_flag						*flags;
	t_queue						*all_queues;
	pthread_mutex_t				id_lock;
	pthread_mutex_t				queue_lock;
	struct timeval				start_time;
	struct timeval				end_time;
	t_nmap						*nmap;
}								t_global;

/*
**	MAIN
*/
void				print_start(t_nmap *nmap);
bool				single_flag(char *flag, bool sub);
void				init_os_scan(t_nmap *nmap);

/*
**	INITIALIZER
*/
void				initializer();

/*
**	HOST
*/
bool				load_hosts(bool multiple_host, t_nmap *nmap);

/*
**	PORTS
*/
bool				load_ports(t_nmap *nmap);

/*
**	GNL
*/
int					get_next_line(int const fd, char **line);

/*
**	SCAN_TYPE
*/
bool				load_scans_type(t_nmap *nmap);

/*
**	FREE
*/
void				free_datas(t_nmap *nmap);

/*
**	THREADS
*/
void				instantiate_threads(t_nmap *nmap);

/*
**	SCANS
*/
void				start_scans(t_thread_handler *handler);

/*
**	CHECKSUM
*/
unsigned short		checksum(unsigned short *ptr, int nbytes);

/*
**  HANDLERS
*/
void					udp_handler(t_thread_handler *thread_handler, char *scan, char *host);
void					tcp_handler(t_thread_handler *thread_handler, char *scan, char *host);
bool					set_ipv4_header(t_thread_handler *thread, int raw_len, char *host, u_char protocol);

/*
**	SOCKET
*/
SOCKET			init_socket(u_char protocol);
bool			send_socket_raw(t_thread_handler *handler, int raw_len, int port);

/*
**	INTERFACE
*/
char			*get_default_interface_host();

/*
**	TCP_FLAGS
*/
void			get_tcp_flags(struct tcphdr *header, char *scan);

/*
**	THREAD_HANDLER
*/
t_thread_handler		*add_thread_handler(t_thread_handler *threads, t_thread_handler *new_thread);

/*
**	PCAP
*/
void					*init_pcap(void *h, t_thread_handler *t);

/*
**	QUEUE
*/
void					add_queue(t_queue *new_queue);
t_queue					*new_queue(int port, u_char proto, char *scan, int id, char *host);
t_queue					*find_queue(u_char proto, int id);

/*
**	PSEUDO_HEADER
*/
char					*get_pseudo_header(int protohdr_len, void *proto_header, u_char proto, struct ip *ip_header);


/*
**  GLOBALS
*/
t_global				*globals;

/*
**  ID
*/
int						get_id(void);

/*
**	DISPLAY
*/
void					display_handler();
void					init_display(t_nmap *nmap);

/*
**	SERVICE
*/
char					*get_port_service(int port, u_char proto);

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
