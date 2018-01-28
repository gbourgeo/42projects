#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_arp.h>
#include <linux/tcp.h>
#include <unistd.h>

#include <sys/ioctl.h>

static bool			init_scan(int *fds)
{	
	// Sending socket.
	fds[0] = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
	if (fds[0] < 0) {
		ft_printf("Failed to instantiate ping scan: `%s'\n", strerror(errno));
		return false;
	}

	// Receiving socket.
	fds[1] = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fds[1] < 0) {
		close(fds[0]);
		ft_printf("Failed to instantiate ping scan: `%s'\n", strerror(errno));
		return false;
	}

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
static uint16_t 		checksum (uint16_t *addr, int len)
{
  int count = len;
  register uint32_t sum = 0;
  uint16_t answer = 0;

  // Sum up 2-byte values until none or only one byte left.
  while (count > 1) {
    sum += *(addr++);
    count -= 2;
  }

  // Add left-over byte, if any.
  if (count > 0) {
    sum += *(uint8_t *) addr;
  }

  // Fold 32-bit sum into 16 bits; we lose information by doing this,
  // increasing the chances of a collision.
  // sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  // Checksum is one's compliment of sum.
  answer = ~sum;

  return (answer);
}

static int 				construct_packet(t_addr *address, char *packet, int port)
{
	int 				packet_len;
	struct ethhdr 		*eth;
	struct iphdr 		*iph;
	struct udphdr 		*uh;
	char 				*data;
	struct sockaddr_ll 	*mac;
	int 				total_len;
	int 				data_len;

	packet_len = sizeof(*eth) + sizeof(*iph) + sizeof(*uh) + 22;
	ft_memset(packet, 0, packet_len);
	total_len = 0;

	/* Construct ETHERNET header */
	eth = (struct ethhdr *)(packet);
	mac = (struct sockaddr_ll *)(&globals.pcap.mac);
	ft_memset(eth->h_dest, 0xff, ETH_ALEN);
	ft_memcpy(eth->h_source, mac->sll_addr, mac->sll_halen);
	eth->h_proto = htons(ETH_P_IP);
	total_len = sizeof(*eth);

	/* Construct IP header */
	iph = (struct iphdr*)(packet + sizeof(*eth));
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->id = htons(42);
	iph->ttl = 255;
	iph->protocol = IPPROTO_UDP;
	inet_pton(AF_INET, globals.pcap.netstr, &iph->saddr);
	inet_pton(AF_INET, address->hostaddr, &iph->daddr);
	total_len += sizeof(*iph);

	/* Construct UDP header */
	uh = (struct udphdr *)(packet + sizeof(*eth) + sizeof(*iph));
	uh->source = htons(4242);
	uh->dest = htons(port);
	uh->check = 0;
	total_len += sizeof(struct udphdr);

	/* We can now had some data */
	data = &packet[total_len];
	data_len = 0;
	data[data_len++] = 'A';
	data[data_len++] = 'B';
	data[data_len++] = 'C';
	data[data_len++] = 'D';
	data[data_len++] = '\0';
	total_len += data_len;

	/* Filling the IP and UDP headers len field */
	iph->tot_len = htons(total_len - sizeof(*eth));
	uh->len = htons((total_len - sizeof(*iph) - sizeof(*eth)));

	/* NOw the IP header checksum */
	iph->check = 0;
	iph->check = checksum((uint16_t *) iph, 20);
	uh->check = 0;
	return total_len;
}

static int 				read_packet(char *buff, int buff_len)
{
	struct ethhdr 	*eth = (struct ethhdr *)(buff);
	unsigned char 	*data;
	int				data_offset = sizeof(struct ethhdr);

	ft_printf("Ethernet Header\n");
	ft_printf("\t|-Source          : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
	ft_printf("\t|-Destination     : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	ft_printf("\t|-Protocol        : %d\n", eth->h_proto);
	if (htons(eth->h_proto) == ETH_P_IP) {
		struct iphdr *ip = (struct iphdr *)(buff + sizeof(struct ethhdr));
		struct sockaddr_in source;
		struct sockaddr_in dest;

		ft_memset(&source, 0, sizeof(source));
		source.sin_addr.s_addr = ip->saddr;
		ft_memset(&dest, 0, sizeof(dest));
		dest.sin_addr.s_addr = ip->daddr;
		ft_printf("IP Header\n");
		ft_printf("\t|-Version         : %d\n", (unsigned int)ip->version);
		ft_printf("\t|-Header Length   : %d DWORDS or %d Bytes\n",(unsigned int)ip->ihl,((unsigned int)(ip->ihl))*4);
		ft_printf("\t|-Type Of Service : %d\n",(unsigned int)ip->tos);
		ft_printf("\t|-Total Length    : %d Bytes\n",ntohs(ip->tot_len));
		ft_printf("\t|-Identification  : %d\n",ntohs(ip->id));
		ft_printf("\t|-Time To Live    : %d\n",(unsigned int)ip->ttl);
		ft_printf("\t|-Protocol        : %d\n",(unsigned int)ip->protocol);
		ft_printf("\t|-Header Checksum : %d\n",ntohs(ip->check));
		ft_printf("\t|-Source IP       : %s\n", inet_ntoa(source.sin_addr));
		ft_printf("\t|-Destination IP  : %s\n", inet_ntoa(dest.sin_addr));
		data_offset += sizeof(struct iphdr);
		if (ip->protocol == IPPROTO_ICMP) {
			struct icmphdr	*icmph;

			icmph = (struct icmphdr *)(buff + sizeof(struct ethhdr) + ip->ihl * 4);
			ft_printf("ICMP Header\n");
			ft_printf("\t|-Message Type  : %d\n", icmph->type);
			ft_printf("\t|-Type Sub-Code : %d\n", icmph->code);
			ft_printf("\t|-Checksum      : %d\n", icmph->checksum);
			ft_printf("\t|-Echo ID       : %d %d\n", ntohs(icmph->un.echo.id), icmph->un.echo.id);
			ft_printf("\t|-Echo Sequence : %d %d\n", ntohs(icmph->un.echo.sequence), icmph->un.echo.sequence);
			ft_printf("\t|-Gateway       : %d %d\n", ntohs(icmph->un.gateway), icmph->un.gateway);
			ft_printf("\t|-MTU           : %d %d\n", ntohs(icmph->un.frag.mtu), icmph->un.frag.mtu);
			data_offset += sizeof(struct icmphdr);
		}
		if (ip->protocol == IPPROTO_TCP) {
			struct tcphdr 	*tcph;

			tcph = (struct tcphdr *)(buff + sizeof(struct ethhdr) + ip->ihl * 4);
			ft_printf("TCP Header\n");
			ft_printf("\t|-Source Port        : %d\n", ntohs(tcph->source));
			ft_printf("\t|-Destination Port   : %d\n", ntohs(tcph->dest));
			ft_printf("\t|-Sequence Number    : %d\n", ntohs(tcph->seq));
			ft_printf("\t|-Acknowledge Number : %d\n", ntohs(tcph->ack_seq));
			ft_printf("\t|-Header Length      : %d\n", ntohs(tcph->seq));
			ft_printf("\t|--------Flags--------\n");
			ft_printf("\t\t|- NA -\n");
			ft_printf("\t|-Window Size        : %d\n", ntohs(tcph->window));
			ft_printf("\t|-Checksum           : %d\n", ntohs(tcph->check));
			ft_printf("\t|-Urgent Pointer     : %d\n", ntohs(tcph->urg_ptr));
			data_offset += sizeof(struct tcphdr);
		}
		else if (ip->protocol == IPPROTO_UDP) {
			struct udphdr 	*uh;

			uh = (struct udphdr *)(buff + sizeof(struct ethhdr) + ip->ihl * 4);
			ft_printf("UDP Header\n");
			ft_printf("\t|-Source Port        :%d\n", ntohs(uh->source));
			ft_printf("\t|-Destination Port   :%d\n", ntohs(uh->dest));
			ft_printf("\t|-UDP Length         :%d\n", ntohs(uh->len));
			ft_printf("\t|-UDP Checksum       :%d\n", ntohs(uh->check));
			data_offset += sizeof(struct udphdr);
		}
		ft_printf("Data\n");
		data = (unsigned char *)(buff + data_offset);
		for (int i = 0; i < buff_len - data_offset; i++) {
			if (i && i % 16 == 0)
				ft_printf("\n");
			ft_printf("%.2X ", data[i]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
	return ft_memcmp(eth->h_dest, globals.pcap.mac.sll_addr, ETH_ALEN);
}

static void				scan_hosts(int *fds)
{
	struct sockaddr_ll 	to;
	static int 			port[] = { 0, 443, 80, 0 };
	int 				port_len = sizeof(port) / sizeof(*port);
	char 				*packet;
	int 				packet_len;

	ft_memset(&to, '\0', sizeof(to));
	to.sll_family = AF_PACKET;
	to.sll_ifindex = if_nametoindex(globals.pcap.device);
	ft_memset(to.sll_addr, 0xff, ETH_ALEN);
	to.sll_halen = ETH_ALEN;

	packet = malloc(sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + 22);
	if (packet == NULL) {
		ft_printf("Can't send packet : insufficient memory.\n");
		return ;		
	}
	for (int i = 0; i < port_len; i++) {
		for (t_addr *address = globals.addresses; address != NULL; address = address->next) {
			if (address->error)
				continue ;
			packet_len = construct_packet(address, packet, port[i]);
			int ret = sendto(fds[0], packet, packet_len, 0, (struct sockaddr *)&to, sizeof(to));
			if (ret == -1) {
				ft_printf("send: %s\n", strerror(errno));
				continue ;
			}
		}
	}

	ft_printf("*************************UDP Packet*************************\n");
return ;
	for (int i = 0; i < port_len; i++) {
		t_addr *address = globals.addresses;
		while (address != NULL) {
			ft_memset(packet, 0, packet_len);
			int ret = recvfrom(fds[1], packet, packet_len, 0, NULL, NULL);
			if (ret == -1) {
				ft_printf("Recvfrom: %s\n", strerror(errno));
				continue ;
			}
			if (read_packet(packet, ret)) 
	 			address = address->next;
 		}
	}
	free(packet);
}

void 				ping_scan()
{
	long 			hms;
	int 			fds[2];

	if (getuid() == 0) {

		gettimeofday(&globals.start, NULL);
		hms = globals.start.tv_sec % 86400;
		hms = (hms + 86400 + 3600) % 86400;
		ft_printf("\nInitiating Ping Scan at %d:%02d\n", hms / 3600, (hms % 3600) / 60);

		if (init_scan(fds)) {

			if (globals.addresses_nb == 1)
				ft_printf("Scanning %s (%s) [4 ports]\n", globals.addresses[0].name, globals.addresses[0].hostaddr);
			else if (globals.addresses_nb > 1)
				ft_printf("Scanning %d hosts [4 ports/host]\n", globals.addresses_nb);

			scan_hosts(fds);
			close(fds[0]);
			close(fds[1]);
			if (init_pcap(PACKET_SIZE, 0, 4000, "")) {
				launch_pcap(pcap_dump);
			}
		}
	}
	else
		ft_printf("Can't scan hosts. Update your privileges.\n");
}
