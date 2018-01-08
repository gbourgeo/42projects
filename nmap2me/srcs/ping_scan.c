#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_arp.h>
#include <unistd.h>

static bool 		init_failed(int *fds)
{
	if (fds[0] > -1)
		close(fds[0]);
	if (fds[1] > -1)
		close(fds[1]);
	ft_printf("Failed to instantiate ping scan: `%s'", strerror(errno));
	return false;
}

static bool			init_scan(int *fds)
{
	long 			hms;
	socklen_t 		on;

	gettimeofday(&globals.start, NULL);
	hms = globals.start.tv_sec % 86400;
	hms = (hms + 86400 + 3600) % 86400;
	ft_printf("\nInitiating Ping Scan at %d:%02d\n", hms / 3600, (hms % 3600) / 60);
	
	ft_memset(fds, -1, 2);
	fds[0] = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (fds[0] < 0)
		return init_failed(fds);
	on = 1;
	if (setsockopt(fds[0], SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)))
		return init_failed(fds);
	on = 1;
	if (setsockopt(fds[0], SOL_IP, IP_HDRINCL, &on, sizeof(on)))
		return init_failed(fds);
	on = 0;
	if (setsockopt(fds[0], SOL_SOCKET, SO_BINDTODEVICE, &on, sizeof(on)))
		return init_failed(fds);

	if (globals.addresses_nb == 1)
		ft_printf("Scanning %s [4 ports]\n", globals.addresses[0].name);
	if (globals.addresses_nb > 1)
		ft_printf("Scanning %d hosts [4 ports/host]\n", globals.addresses_nb);

	struct sockaddr_ll	ll;

	fds[1] = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fds[1] < 0)
		return init_failed(fds);
	ft_memset(&ll, 0, sizeof(ll));
	ll.sll_family = AF_PACKET;
	ll.sll_protocol = htons(ETH_P_ALL);
	ll.sll_ifindex = if_nametoindex(globals.pcap.device);
	ll.sll_hatype = ARPHRD_NETROM;
	ll.sll_pkttype = PACKET_HOST;
	ll.sll_halen = 0;
	if (bind(fds[1], (struct sockaddr *)&ll, sizeof(ll)))
		return init_failed(fds);
	return true;
}

/*
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

static void 			read_packet(char *buff)
{
	struct ethhdr *eth = (struct ethhdr *)(buff);

	ft_printf("Source : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
	ft_printf("Destin : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	ft_printf("Proto  : %d %d\n", eth->h_proto, ETH_P_IP);
	if (htons(eth->h_proto) == ETH_P_IP) {
		struct iphdr *ip = (struct iphdr *)(buff + sizeof(struct ethhdr));
		struct sockaddr_in source;
		struct sockaddr_in dest;

		ft_memset(&source, 0, sizeof(source));
		source.sin_addr.s_addr = ip->saddr;
		ft_memset(&dest, 0, sizeof(dest));
		dest.sin_addr.s_addr = ip->daddr;
		ft_printf("\tVersion : %d\n", (unsigned int)ip->version);
		ft_printf("\t|-Internet Header Length : %d DWORDS or %d Bytes\n",(unsigned int)ip->ihl,((unsigned int)(ip->ihl))*4);
		ft_printf("\t|-Type Of Service : %d\n",(unsigned int)ip->tos);
		ft_printf("\t|-Total Length : %d Bytes\n",ntohs(ip->tot_len));
		ft_printf("\t|-Identification : %d\n",ntohs(ip->id));
		ft_printf("\t|-Time To Live : %d\n",(unsigned int)ip->ttl);
		ft_printf("\t|-Protocol : %d\n",(unsigned int)ip->protocol);
		ft_printf("\t|-Header Checksum : %d\n",ntohs(ip->check));
		ft_printf("\t|-Source IP : %s\n", inet_ntoa(source.sin_addr));
		ft_printf("\t|-Destination IP : %s\n",inet_ntoa(dest.sin_addr));
	}
}

static char 			*construct_packet(t_addr *address)
{
	int 				packet_len;
	char 				*packet;
	struct ethhdr 		*eth;
	struct iphdr 		*iph;
	struct udphdr 		*uh;
	struct sockaddr_ll 	*mac;
	struct sockaddr_in 	*v4;
	int 				total_len;

	packet_len = sizeof(*eth) + sizeof(*iph) + sizeof(*uh) + 22;
	ft_printf("mallocin' : %d\n", packet_len);
	packet = malloc(sizeof(*packet) * packet_len);
	if (packet == NULL)
		return NULL;
	ft_memset(packet, 0, packet_len);

	/* Construct ETHERNET header */
	eth = (struct ethhdr *)(packet);
	mac = (struct sockaddr_ll *)(&globals.pcap.mac);
	for (int i = 0; i < ETH_ALEN; i++)
		eth->h_dest[i] = 0;
	for (int i = 0; i < mac->sll_halen; i++)
		eth->h_source[i] = mac->sll_addr[i];
	eth->h_proto = htons(ETH_P_IP);
	total_len = sizeof(*eth);

	/* Construct IP header */
	iph = (struct iphdr*)(packet + sizeof(*eth));
	v4 = (struct sockaddr_in *)(&globals.pcap.v4);
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 16;
	iph->id = htons(10201);
	iph->ttl = 64;
	iph->protocol = 17;
	iph->saddr = inet_addr(inet_ntoa(v4->sin_addr));
	iph->daddr = inet_addr(address->name);	 
	total_len += sizeof(*iph);

	/* Construct UDP header */
	uh = (struct udphdr *)(pcaket + sizeof(*eth) + sizeof(*iph));
	uh->source = htons(23451);
	uh->dest = htons(23452);
	uh->check = 0;
	total_len+= sizeof(struct udphdr);

	/* We can now had some data */
	packet[total_len++] = 'A';
	packet[total_len++] = 'B';
	packet[total_len++] = 'C';
	packet[total_len++] = 'D';

	/* Filling the IP and UDP headers len field */
	uh->len = htons((total_len - sizeof(*iph) - sizeof(*eth)));
	iph->tot_len = htons(total_len -sizeof(*eth));
	(void)total_len;
	return packet;
}

static void				scan_hosts(int *fds)
{
	struct sockaddr_in	addr;
	socklen_t 			len = sizeof(struct sockaddr);
	static int 			port[] = { 0, 443, 80, 0 };
	int 				port_len = sizeof(port) / sizeof(*port);
	char 				*packet;
	char 				buff[PACKET_SIZE];

	for (int i = 0; i < port_len; i++) {
		for (t_addr *ptr = globals.addresses; ptr != NULL; ptr = ptr->next) {
			if (ptr->error)
				continue ;
			packet = construct_packet(ptr);
			if (packet == NULL) {
				ft_printf("Can't send packet : insufficient memory.\n");
				return ;
			}
			return ;
			int ret = sendto(fds[0], ptr->buff, PACKET_SIZE, 0, (struct sockaddr *)&addr, len);
			if (ret == -1)
				ft_printf("send: %s\n", strerror(errno));
			ft_printf("Sent %d : %d\n", ret, PACKET_SIZE);
		}
	}
	for (int i = 0; i < port_len; i++) {
		for (t_addr *ptr = globals.addresses; ptr != NULL; ptr = ptr->next) {
			ft_memset(buff, 0, sizeof(buff))	;
			ft_memset(&addr, 0, sizeof(addr));
			int ret = recvfrom(fds[1], buff, PACKET_SIZE, 0, (struct sockaddr *)&addr, &len);
			if (ret == -1) {
				ft_printf("Recvfrom %s\n", strerror(errno));
				continue ;
			}
			ft_printf("Received : %d\n", ret);
			read_packet(buff);
		}
	}
}

void 				ping_scan()
{
	int 			fds[2];

	if (getuid() == 0) {
		if (init_scan(fds)) {
			scan_hosts(fds);
			return ;
			if (init_pcap(PACKET_SIZE, 1, 1000, "")) {
				launch_pcap(pcap_dump);
			}
			close(fds[0]);
			close(fds[1]);
		}
	}
	else
		ft_printf("Can't scan hosts. Update your privileges.\n");
}
