/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 13:59:36 by frmarinh          #+#    #+#             */
/*   Updated: 2020/03/28 16:29:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <pthread.h>
# include <pcap/pcap.h>
# include <netinet/in.h>
# include <ifaddrs.h>
# include <linux/if_packet.h>

# define DEFAULT_THREADS 		1
# define NM_MAX_PORTS_SCAN 		1024
# define MAX_THREADS_NUMBER		250
# define SUPPORTED_SCANS		"SYN/NULL/FIN/XMAS/ACK/UDP"
# define DEFAULT_PCAP_TIMEOUT	2000
# define DEFAULT_TTL			64
# define PACKET_SIZE 			1024

/*
    96 bit (12 bytes) pseudo header needed for tcp header checksum calculation
*/
/*
struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t length;
};
*/

typedef struct 			s_addr
{
	char 				*name;
	char 				hostaddr[255];
	struct s_addr 		*next;
	struct s_addr 		*prev;
}						t_addr;

typedef struct			s_data
{
	t_addr				*addr;
	char				*scan;
	int					port;
}						t_data;

typedef struct 			s_thread
{
	int 				nb;
	int 				opes;
	t_data				*data;
	pthread_t 			id;
}						t_thread;

typedef struct 			s_pcap
{
	char 				*device;
	pcap_t 				*handle;
	bpf_u_int32 		net;
	char 				netstr[INET_ADDRSTRLEN];
	bpf_u_int32 		mask;
	char 				maskstr[INET_ADDRSTRLEN];
	struct bpf_program	fp;
	struct sockaddr_ll 	mac;
	struct sockaddr_in 	v4;
	struct sockaddr_in6 v6;
	int 				timeout;
}						t_pcap;

typedef struct			s_parameters
{
	char 				*progname;
	int 				*ports;
	char				**scans;
	t_addr 				*addresses;
	t_thread			**threads;
	int 				ports_nb;
	int					scans_nb;
	int 				addresses_nb;
	int 				threads_nb;
	int					pcap_timeout;

	char				*device;
	time_t				start;
	pcap_t				*handle;
}						t_params;

typedef struct			s_global
{
	pthread_mutex_t		id_lock;
	int					recv_timeout;
	char				*device;
	t_data				*data;
}						t_global;

/*
**  GLOBAL
*/
t_global					g_global;

/*
**	ERROR
*/
void 					nmap_error(t_params *e, char *str, ...);

/*
**	OTHER
*/
void					get_options(char **argv, t_params *e);
void 					get_interface(t_params *e);
void 					init_threads(t_params *e);
int						init_socket(unsigned char protocol, int timeout);
int						init_ipv4_hdr(char raw[], char *device, char *addr, unsigned char protocol);
unsigned short			checksum(unsigned short *ptr, int nbytes);
void					init_tcp_hdr(char raw[], int port, char *scan, char *device);
int						get_id(void);
void 					ping_scan(void);

/*
**	PCAP
*/
void 					init_pcap(t_params *e);
void 					launch_pcap(void (*handler)());

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
