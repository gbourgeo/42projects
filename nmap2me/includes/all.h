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

# include <sys/time.h>

# define bool 				int
# define true 				1
# define false 				0
# define DEFAULT_THREADS 	1
# define MAX_PORTS_SCAN 	1024
# define MAX_PORT_NUMBER	65535
# define MAX_THREADS_NUMBER	250
# define DEFAULT_TTL		64

# define AVAILABLE_OPTIONS  { "help",	"Print this help screen and return" },						\
							{ "ports", 	"[1024 max] Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)" },	\
							{ "ip", 	"Ip address to scan in dot format" },						\
							{ "file", 	"File name containing IP addresses to scan" },				\
							{ "speedup","[250 max] Number of parallel threads to use" },			\
							{ "scan", 	"SYN/NULL/FIN/XMAS/ACK/UDP" },								\
/*							{ "deep", 	"Scans all addresses from a given host" },					\
							{ "src",	"Spoof the src address" },									\
							{ "timeout","Wait time for host answer (seconds or ms)" },				\
							{ "osscan",	"Scan the host single threaded for guessing the OS" },		\
							{ "closed",	"Show closed ports too on display" },						\
*/							{ NULL }

enum 				options
{
	NM_HELP = 0,
	NM_PORTS,
	NM_IP,
	NM_FILE,
	NM_SPEEDUP,
	NM_SCANS,
	NM_DEEP,
	NM_SRC,
	NM_TIMEOUT,
	NM_OSSCAN,
	NM_CLOSED,
	NM_OPTIONS_LEN,
};

enum 				scan_types
{
	NM_SYN	= 0x0001,
	NM_NULL	= 0x0002,
	NM_FIN	= 0x0004,
	NM_XMAS	= 0x0008,
	NM_ACK	= 0x0010,
	NM_UDP 	= 0x0020,
};

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
typedef struct			s_global
{
	char 				*progname;
	char				**flags;
	int 				ports_nb;
	int 				ports[MAX_PORTS_SCAN];
	int 				scan_nb;
	int 				scan_types;
	int 				addresses_nb;
	char 				**addresses;
	int 				threads_nb;
	struct timeval		start_time;
}						t_global;

/*
**  GLOBAL
*/
t_global				globals;

/*
**	ERROR
*/
void 					nmap_error(char *str, ...);

/*
**	PARAMETERS
*/
void					get_ports_parameters();
void 					get_scans_parameters();
void 					get_threads_parameters();
void 					get_ip_parameters();

/*
**	OTHER
*/
void 					start_mapping();

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
