#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <linux/tcp.h>
#include <netinet/udp.h>

#include "libft.h"
#include "ft_printf.h"
#include "all.h"

static void 			print_ethernet_header(void *data)
{
	struct ethhdr 		*eth = (struct ethhdr *)data;

	ft_printf("Ethernet Header\n");
	ft_printf("\t|-Source          : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
	ft_printf("\t|-Destination     : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	ft_printf("\t|-Protocol        : %d\n", eth->h_proto);
}

static void 			print_ip_header(void *data)
{
	struct iphdr 		*ip = (struct iphdr *)data;
	struct sockaddr_in	source;
	struct sockaddr_in	dest;

	ft_memset(&source, 0, sizeof(source));
	ft_memset(&dest, 0, sizeof(dest));
	source.sin_addr.s_addr = ip->saddr;
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
}

static void 			print_icmp_header(void *data)
{
	struct icmphdr 		*icmp = (struct icmphdr *)data;

	ft_printf("ICMP Header\n");
	ft_printf("\t|-Message Type  : %d\n", icmp->type);
	ft_printf("\t|-Type Sub-Code : %d\n", icmp->code);
	ft_printf("\t|-Checksum      : %d\n", icmp->checksum);
	ft_printf("\t|-Echo ID       : %d %d\n", ntohs(icmp->un.echo.id), icmp->un.echo.id);
	ft_printf("\t|-Echo Sequence : %d %d\n", ntohs(icmp->un.echo.sequence), icmp->un.echo.sequence);
	ft_printf("\t|-Gateway       : %d %d\n", ntohs(icmp->un.gateway), icmp->un.gateway);
	ft_printf("\t|-MTU           : %d %d\n", ntohs(icmp->un.frag.mtu), icmp->un.frag.mtu);
}

static void 		print_tcp_header(void *data)
{
	struct tcphdr 	*tcp = (struct tcphdr *)data;

	ft_printf("TCP Header\n");
	ft_printf("\t|-Source Port        : %d\n", ntohs(tcp->source));
	ft_printf("\t|-Destination Port   : %d\n", ntohs(tcp->dest));
	ft_printf("\t|-Sequence Number    : %d\n", ntohs(tcp->seq));
	ft_printf("\t|-Acknowledge Number : %d\n", ntohs(tcp->ack_seq));
	ft_printf("\t|-Header Length      : %d\n", ntohs(tcp->seq));
	ft_printf("\t|--------Flags--------\n");
	ft_printf("\t\t|- NA -\n");
	ft_printf("\t|-Window Size        : %d\n", ntohs(tcp->window));
	ft_printf("\t|-Checksum           : %d\n", ntohs(tcp->check));
	ft_printf("\t|-Urgent Pointer     : %d\n", ntohs(tcp->urg_ptr));
}

static void			print_udp_header(void *data)
{
	struct udphdr *udp = (struct udphdr *)data;

	ft_printf("UDP Header\n");
	ft_printf("\t|-Source Port        :%d\n", ntohs(udp->source));
	ft_printf("\t|-Destination Port   :%d\n", ntohs(udp->dest));
	ft_printf("\t|-UDP Length         :%d\n", ntohs(udp->len));
	ft_printf("\t|-UDP Checksum       :%d\n", ntohs(udp->check));
}

static void 		print_data(void *data, int data_len)
{
	unsigned char 	*dt = (unsigned char *)data;

	ft_printf("Data\n");
	for (int i = 0; i < data_len; i++) {
		if (i && i % 16 == 0)
			ft_printf("\n");
		ft_printf("%.2X ", dt[i]);
	}
	ft_printf("\n\n");
}

static void			print_packet_info(char *buff, int buff_len, char *str, int data_offset)
{
	ft_printf("****************************%s Packet****************************\n", str);

	print_ethernet_header(buff);

	if (htons(((struct ethhdr *)(buff))->h_proto) == ETH_P_IP) {

		print_ip_header(buff + sizeof(struct ethhdr));

		int protocol = ((struct iphdr *)(buff + sizeof(struct ethhdr)))->protocol;
		if (protocol == IPPROTO_ICMP) {
			print_icmp_header(buff + sizeof(struct ethhdr) + sizeof(struct iphdr));
		} else if (protocol == IPPROTO_TCP) {
			print_tcp_header(buff + sizeof(struct ethhdr) + sizeof(struct iphdr));
		} else if (protocol == IPPROTO_UDP) {
			print_udp_header(buff + sizeof(struct ethhdr) + sizeof(struct iphdr));
		} else {
			ft_printf("Protocol: %d\n", protocol);
		}
	}
	print_data(buff + data_offset, buff_len - data_offset);
}

int 				read_packet(char *buff, int buff_len)
{
	struct ethhdr 	*eth = (struct ethhdr *)(buff);
	struct iphdr 	*ip = (struct iphdr *)(buff + sizeof(struct ethhdr));
	int				data_offset = sizeof(struct ethhdr);

	if (htons(eth->h_proto) == ETH_P_IP) {
		data_offset += sizeof(struct iphdr);
		if (ip->protocol == IPPROTO_ICMP) {
//			struct icmphdr *icmp = (struct icmphdr *)(buff + sizeof(struct ethhdr) + ip->ihl * 4);
			data_offset += sizeof(struct icmphdr);
			print_packet_info(buff, buff_len, "ICMP", data_offset);
		} else if (ip->protocol == IPPROTO_TCP) {
//			struct tcphdr *tcp = (struct tcphdr *)(buff + sizeof(struct ethhdr) + ip->ihl * 4);
			data_offset += sizeof(struct tcphdr);
			print_packet_info(buff, buff_len, "TCP", data_offset);
		} else if (ip->protocol == IPPROTO_UDP) {
//			struct udphdr *udp = (struct udphdr *)(buff + sizeof(struct ethhdr) + ip->ihl * 4);
			data_offset += sizeof(struct udphdr);
			print_packet_info(buff, buff_len, "UDP", data_offset);
		} else {
			print_packet_info(buff, buff_len, "???", data_offset);
		}
	} else {
		print_packet_info(buff, buff_len, "???", data_offset);
	}
	return ft_memcmp(eth->h_dest, globals.pcap.mac.sll_addr, ETH_ALEN);
}
