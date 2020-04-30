
#include <linux/if_ether.h>
#include <netinet/ether.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <signal.h>

#include "all.h"
#include "libft.h"
#include "ft_printf.h"

struct proto
{
	short		value;
	const char	*name;
};

static const char		*get_prot(struct proto prot[], long size, short value)
{
	for (long i = 0; i < size; i++)
		if (prot[i].value == value)
			return (prot[i].name);
	return ("Unknown");
}

/*static void		print_eth_hdr(struct ethhdr *eth)
{
	struct proto	prot[] = {
		{ 0x0800, "IPv4"},
		{ 0x0806, "ARP" },
		{ 0x8137, "IPX" },
		{ 0x86dd, "IPv6" },
	};
	short		value;

	value = ntohs(eth->h_proto);
	ft_printf("ETH HEADER:\n");
	ft_printf("%-20s\t| %-20s\t| Protocol\n", "Dest", "Source");
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x | %02x:%02x:%02x:%02x:%02x:%02x\n",
		eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5],
		eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]
	);
	ft_printf("%-20s\t| %-20s\t| %s (%#.04X)\n",
		ether_ntoa((struct ether_addr *)eth->h_dest),
		ether_ntoa((struct ether_addr *)eth->h_source),
		get_prot(prot, sizeof(prot) / sizeof(prot[0]), value),
		value);
}*/

void		print_ip_hdr(struct iphdr *ip)
{
	struct proto	prot[] = {
		{ IPPROTO_IP, "IP" },			/* Dummy protocol for TCP.  */
		{ IPPROTO_ICMP, "ICMP" },		/* Internet Control Message Protocol.  */
		{ IPPROTO_IGMP, "IGMP" },		/* Internet Group Management Protocol. */
		{ IPPROTO_IPIP, "IPIP" },		/* IPIP tunnels (older KA9Q tunnels use 94).  */
		{ IPPROTO_TCP, "TCP" },			/* Transmission Control Protocol.  */
		{ IPPROTO_EGP, "EGP" },			/* Exterior Gateway Protocol.  */
		{ IPPROTO_PUP, "PUP" },		/* PUP protocol.  */
		{ IPPROTO_UDP, "UDP" },		/* User Datagram Protocol.  */
		{ IPPROTO_IDP, "IDP" },		/* XNS IDP protocol.  */
		{ IPPROTO_TP, "TP" },			/* SO Transport Protocol Class 4.  */
		{ IPPROTO_DCCP, "DCCP" },		/* Datagram Congestion Control Protocol.  */
		{ IPPROTO_IPV6, "IPV6" },		/* IPv6 header.  */
		{ IPPROTO_RSVP, "RSVP" },		/* Reservation Protocol.  */
		{ IPPROTO_GRE, "GRE" },		/* General Routing Encapsulation.  */
		{ IPPROTO_ESP, "ESP" },		/* encapsulating security payload.  */
		{ IPPROTO_AH, "AH" },			/* authentication header.  */
		{ IPPROTO_MTP, "MTP" },		/* Multicast Transport Protocol.  */
		{ IPPROTO_BEETPH, "BEETPH" },		/* IP option pseudo header for BEET.  */
		{ IPPROTO_ENCAP, "ENCAP" },		/* Encapsulation Header.  */
		{ IPPROTO_PIM, "PIM" },		/* Protocol Independent Multicast.  */
		{ IPPROTO_COMP, "COMP" },		/* Compression Header Protocol.  */
		{ IPPROTO_SCTP, "SCTP" },		/* Stream Control Transmission Protocol.  */
		{ IPPROTO_UDPLITE, "UDPLITE" },	/* UDP-Lite protocol.  */
		{ IPPROTO_MPLS, "MPLS" },		/* MPLS in IP.  */
		{ IPPROTO_RAW, "RAW" },		/* Raw IP packets.  */
	};

	ft_printf("IP HEADER:\n");
	ft_printf("ihl | version | tos | tot_len | id    | frag_off | ttl | protocol | check | %-15s | daddr\n", "saddr");
	ft_printf("%3d | %7d | %3hhu | %7hu | %5hu | %8hu | %3hhu | %8s | %5hu | %-15s | %s\n",
	ip->ihl,
	ip->version,
	ip->tos,
	ntohs(ip->tot_len),
	ntohs(ip->id),
	ip->frag_off,
	ip->ttl,
	get_prot(prot, sizeof(prot) / sizeof(prot[0]), ip->protocol),//ip->protocol,
	ntohs(ip->check),
	inet_ntoa(*(struct in_addr *)&ip->saddr),
	inet_ntoa(*(struct in_addr *)&ip->daddr)
	);
}

void		print_tcp_hdr(struct tcphdr *tcp)
{
	ft_printf("TCP HEADER:\n");
	ft_printf("source | %-5s | %-11s | %-11s | res1 | doff | fin | syn | rst | psh | ack | urg | ece | cwr | window | check | urg_ptr\n", "dest", "seq", "ack_seq");
	ft_printf("%6u | %5u | %11u | %11u | %4d | %4d | %3d | %3d | %3d | %3d | %3d | %3d | %3d | %3d | %6d | %5d | %d\n",
	ntohs(tcp->source),
	ntohs(tcp->dest),
	ntohl(tcp->seq),
	ntohl(tcp->ack_seq),
	tcp->res1,
	tcp->doff,
	tcp->fin,
	tcp->syn,
	tcp->rst,
	tcp->psh,
	tcp->ack,
	tcp->urg,
	tcp->ece,
	tcp->cwr,
	tcp->window,
	tcp->check,
	tcp->urg_ptr
	);
}

/*static void print_data_back(u_char *data, int len)
{
	int i = 0;

	ft_printf("Lenght: %d\n", len);
	while (i < len)
	{
		if (i && (i) % 16 == 0)
		{
			int y = i - 16;
			while (y < i)
			{
				if (ft_isprint(data[y]))
					write(1, data + y, 1);
				else
					write(1, ".", 1);
				y++;
			}
			write(1, "\n", 1);
		}
		ft_printf("%02X ", data[i]);
		i++;
	}
	int y = i;
	while (y % 16 != 0)
		y--;
	for (int k = 0; k < (16 - (i - y)); k++)
		write(1, "   ", 3);
	while (y < i)
	{
		if (ft_isprint(data[y]))
			write(1, data + y, 1);
		else
			write(1, ".", 1);
		y++;
	}
	write(1, "\n", 1);
}*/

void			pcap_dump(unsigned char *user, const struct pcap_pkthdr *h,
const unsigned char *bytes)
{
	t_params		*e;
	struct ethhdr	*eth;
	struct iphdr	*ip;
	
	(void)h;
	e = (t_params *)user;
	eth = (struct ethhdr *)bytes; // link layer header
	ip = (struct iphdr *)(bytes + sizeof(*eth));
	// if (0)
	// {
	// 	print_eth_hdr(eth);
	// 	print_ip_hdr(ip);
	// }
	if (ip->protocol == IPPROTO_TCP)
	{
		struct tcphdr	*tcp_header;
		int				id_dst;
		t_data			*data;

		tcp_header = (struct tcphdr*)(bytes + sizeof(*eth) + sizeof(*ip));
		id_dst = ntohs(tcp_header->dest);
		data = find_data(IPPROTO_TCP, id_dst, e);
		if (data)
		{
			// print_tcp_hdr(tcp_header);
			// print_data_back((u_char *)(tcp_header + 1), ntohs(ip->tot_len) - sizeof(struct iphdr) - sizeof(struct tcphdr));
			data->response.received = 1;
			if (!ft_strcmp(data->scan, "SYN"))
			{
				if (tcp_header->syn)
				{
					if (e->verbose || e->debug)
						ft_printf("Discovered open port %d/tcp on %s\n", data->port, data->addr->hostaddr);
					data->response.open = 1;
				}
				else if (tcp_header->rst)
				{
					if (e->verbose || e->debug)
						ft_printf("Discovered closed port %d/tcp on %s\n", data->port, data->addr->hostaddr);
					data->response.filtered = 0;
				}
			}
			ft_memcpy(data->response.raw, ip, sizeof(*ip) + sizeof(*tcp_header));
		}
	}
	else if (ip->protocol == IPPROTO_ICMP)
	{
		struct icmp		*icmp;

		icmp = (struct icmp *)(bytes + sizeof(*eth) + sizeof(*ip));
		ft_printf("ICMP %p\n", icmp);
	}
}

void				launch_pcap(t_params *e)
{
	struct timeval tm;
	unsigned long start;
	unsigned long end;
	int			ret;

	gettimeofday(&tm, NULL);
	start = tm.tv_sec * (int)1e6 + tm.tv_usec;
	end = start;
	ret = 0;
	while (end - start < (unsigned long)(e->tcp_timeout * 1000 * e->retry))
	{
		ret = pcap_dispatch(g_global.handle, -1, pcap_dump, (u_char *)e);
		if (ret == -1)
			nmap_error(e, "ERROR: error reading packets from interface %s: %s",
				e->pcap.device, pcap_geterr(g_global.handle));
		gettimeofday(&tm, NULL);
		end = tm.tv_sec * (int)1e6 + tm.tv_usec;
	}
	gettimeofday(&e->end_time, NULL);
	e->packet_read += ret;
	if (e->verbose || e->debug)
	{
		ft_printf("Completed");
		for (int i = 0; e->scans[i]; i++)
				ft_printf(" %s", e->scans[i]);
		unsigned long ssec = e->start_time.tv_sec * (int)1e6 + e->start_time.tv_usec;
		unsigned long esec = e->end_time.tv_sec * (int)1e6 + e->end_time.tv_usec;
		printf(" Scan at %s, %.2fs elapsed (%d total ports)\n",
			get_time("%H:%M", &e->end_time),
			(double)(esec - ssec) / (int)1e6,
			e->addresses_nb * e->ports_nb * e->scans_nb);
	}
}
