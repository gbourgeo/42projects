
#include "all.h"
#include "libft.h"
#include "ft_printf.h"
#include "tcp.h"

#include <netinet/ip.h>
#include <linux/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int			init_ipv4_hdr(char raw[], char *device, char *addr, unsigned char protocol)
{
	struct ip	*ip;

	ip = (struct ip *)raw;
	ft_memset(ip, 0, sizeof(*ip));
	ip->ip_src.s_addr = inet_addr(device);
	if (!inet_pton(AF_INET, addr, &ip->ip_dst))
	{
		ft_printf("ERROR: can't set destination address \"%s\"\n", addr);
		return (0);
	}
	ip->ip_ttl = DEFAULT_TTL;
	ip->ip_p = protocol;
	ip->ip_v = 4;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_len = htons(sizeof(struct ip) + sizeof(struct tcphdr));
	ip->ip_off = 0;
	ip->ip_id = htons(999);
	ip->ip_sum = 0;
	ip->ip_sum = checksum((unsigned short *)ip, sizeof(*ip));
	return (1);
}

static void	set_tcp_flags(struct tcphdr *tcp, char *scan)
{
	if (!ft_strcmp(scan, "SYN"))
	{
		tcp->syn = 1;
	}
	else if (!ft_strcmp(scan, "FIN"))
	{
		tcp->fin = 1;
	}
	else if (!ft_strcmp(scan, "NULL"))
	{
		tcp->urg = 0;
		tcp->ack = 0;
		tcp->psh = 0;
		tcp->rst = 0;
		tcp->syn = 0;
		tcp->fin = 0;
	}
	else if (!ft_strcmp(scan, "XMAS"))
	{
		tcp->urg = 1;
		tcp->psh = 1;
		tcp->fin = 1;
	}
	else if (!ft_strcmp(scan, "ACK"))
	{
		tcp->ack = 1;
	}
}

static void	set_tcp_pseudogram(char psg[], struct tcphdr *tcp, struct ip *ip, char *device)
{
	struct pseudo_header	*psh;

	psh = (struct pseudo_header *)psg;
	psh->source_address = inet_addr(device);
	psh->dest_address = ip->ip_dst.s_addr;
	psh->placeholder = 0;
	psh->protocol = IPPROTO_TCP;
	psh->length = htons(sizeof(struct tcphdr));
	ft_memcpy(psg + sizeof(*psh), tcp, sizeof(*tcp));
}

void			init_tcp_hdr(char raw[], int port, char *scan, char *device)
{
	struct tcphdr	*tcp;
	char			psg[sizeof(struct pseudo_header) + sizeof(struct tcphdr)];

	tcp = (struct tcphdr *)(raw + sizeof(struct ip));
	tcp->source = htons(get_id());
	tcp->dest = htons(port);
	tcp->seq = htonl(1);
	tcp->ack_seq = 1;
	tcp->doff = 5;
	tcp->res1 = 0;
	tcp->cwr = 0;
	tcp->ece = 0;
	tcp->urg = 0;
	tcp->ack = 0;
	tcp->psh = 0;
	tcp->rst = 0;
	tcp->syn = 0;
	tcp->fin = 0;
	tcp->window = htons(5840);
	tcp->urg_ptr = 0;
	tcp->check = 0;
	set_tcp_flags(tcp, scan);
	ft_memset(psg, 0, sizeof(psg));
	set_tcp_pseudogram(psg, tcp, (struct ip *)raw, device);
	tcp->check = checksum((unsigned short *)psg, sizeof(psg));
}
