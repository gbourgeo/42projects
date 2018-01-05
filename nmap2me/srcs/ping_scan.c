#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <linux/if_arp.h>

static void			init_scan(int *fds)
{
	long 			hms;
	socklen_t 		on;

	gettimeofday(&globals.start, NULL);
	hms = globals.start.tv_sec % 86400;
	hms = (hms + 86400 + 3600) % 86400;
	ft_printf("\nInitiating Ping Scan at %d:%02d\n", hms / 3600, (hms % 3600) / 60);
	
	fds[0] = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (fds[0] < 0)
		nmap_error("Failed to instantiate ping scan: `%s'", strerror(errno));
	on = 1;
	if (setsockopt(fds[0], SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)))
		nmap_error("Failed to instantiate ping scan: `%s'", strerror(errno));
	on = 1;
	if (setsockopt(fds[0], SOL_IP, IP_HDRINCL, &on, sizeof(on)))
		nmap_error("Failed to instantiate ping scan: `%s'", strerror(errno));
	on = 0;
	if (setsockopt(fds[0], SOL_SOCKET, SO_BINDTODEVICE, &on, sizeof(on)))
		nmap_error("Failed to instantiate ping scan: `%s'", strerror(errno));

	if (globals.addresses_nb == 1)
		ft_printf("Scanning %s [4 ports]\n", globals.addresses[0].name);
	if (globals.addresses_nb > 1)
		ft_printf("Scanning %d hosts [4 ports/host]\n", globals.addresses_nb);

	struct sockaddr_ll	ll;

	fds[1] = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fds[1] < 0)
		nmap_error("Failed to instantiate ping scan: `%s'", strerror(errno));
	ll.sll_family = AF_PACKET;
	ll.sll_protocol = htons(ETH_P_ALL);
	ll.sll_ifindex = if_nametoindex(globals.pcap.device);
	ll.sll_hatype = ARPHRD_NETROM;
	ll.sll_pkttype = PACKET_HOST;
	ll.sll_halen = 0;
	if (bind(fds[1], (struct sockaddr *)&ll, sizeof(ll)))
		nmap_error("Failed to instantiate ping scan: `%s'", strerror(errno));
}

/*
static unsigned short csum(unsigned short *buf, int nwords)

{       //

        unsigned long sum;

        for(sum=0; nwords>0; nwords--)

                sum += *buf++;

        sum = (sum >> 16) + (sum &0xffff);

        sum += (sum >> 16);

        return (unsigned short)(~sum);

}

struct ip {
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	ip_hl:4,		// header length //
		ip_v:4;			// version //
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	ip_v:4,			// version //
		ip_hl:4;		// header length //
#endif
	u_char	ip_tos;			// type of service //
	short	ip_len;			// total length //
	u_short	ip_id;			// identification //
	short	ip_off;			// fragment offset field //
#define	IP_DF 0x4000			// dont fragment flag //
#define	IP_MF 0x2000			// more fragments flag //
	u_char	ip_ttl;			// time to live //
	u_char	ip_p;			// protocol //
	u_short	ip_sum;			// checksum //
	struct	in_addr ip_src,ip_dst;	// source and dest address //
};
*/
static void 		ip_header(char *packet, const char *src, const char *dst)
{
	struct ip 		*ip = (struct ip *)packet;

	ip->ip_hl = sizeof(*ip) >> 2;
	ip->ip_v = 4;
	ip->ip_tos = 0;
	ip->ip_len = htons(PACKET_SIZE);
	ip->ip_id = htons(4242);
	ip->ip_off = htons(0);
	ip->ip_ttl = 255;
	ip->ip_p = 1;
	ip->ip_sum = 0;
//	ip->ip_sum = csum((unsigned short *)ip, sizeof(struct ip));
	ip->ip_src.s_addr = inet_addr(src);
	if (!inet_pton(AF_INET, dst, &ip->ip_dst))
		ft_printf("Dest network address %s not valid.\n", dst);
}

static void 		icmp_header(struct ip *packet)
{
	struct icmphdr 	*icmp = (struct icmphdr *)(packet + 1);

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->checksum = htons(~(ICMP_ECHO << 8));
}

static void 		scan_hosts(int *fds)
{
	struct sockaddr_in	addr;
	socklen_t 			len = sizeof(struct sockaddr);
	static int 			port[] = { 0, 443, 80, 0 };
	int 				port_len = sizeof(port) / sizeof(*port);
	char 				buff[PACKET_SIZE];

	ft_memset(buff, 0, sizeof(buff));
	for (int i = 0; i < port_len; i++) {
		for (t_addr *ptr = globals.addresses; ptr != NULL; ptr = ptr->next) {
			if (ptr->error)
				continue ;
			ip_header(buff, globals.pcap.device, ptr->hostaddr);
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port[i]);
			addr.sin_addr.s_addr = inet_addr(ptr->hostaddr);
			ft_bzero(addr.sin_zero, sizeof(addr.sin_zero));
			icmp_header((struct ip *)buff);
//			ft_strncpy((char *)ptr->buff, "Hello !", sizeof(ptr->buff));
			int ret = sendto(fds[0], ptr->buff, PACKET_SIZE, 0, (struct sockaddr *)&addr, len);
			if (ret != PACKET_SIZE)
				ft_printf("Sent error %d != %d\n", ret, PACKET_SIZE);
		}
	}
	for (int i = 0; i < port_len; i++) {
		for (t_addr *ptr = globals.addresses; ptr != NULL; ptr = ptr->next) {
			ft_memset(buff, 0, sizeof(buff));
			ft_memset(&addr, 0, sizeof(addr));
			int ret = recvfrom(fds[1], buff, sizeof(buff), MSG_TRUNC, (struct sockaddr *)&addr, &len);
			if (ret == -1)
				ft_printf("Recvfrom %s\n", strerror(errno));
			else
				ft_printf("Received %d : %s ; %d %d,%d %s\n", ret, buff, addr.sin_family, addr.sin_port, ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
		}
	}
}

void 				ping_scan()
{
	int 			fds[2];

	init_scan(fds);
	scan_hosts(fds);
	if (init_pcap(PACKET_SIZE, 0, 2000, "")) {
		launch_pcap(pcap_dump);
	}
}
