
#include "all.h"
#include "libft.h"
#include "ft_printf.h"
#include "tcp.h"

#include <netinet/ip.h>
#include <linux/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void		init_ipv4_hdr(char raw[], struct sockaddr_in *to, u_int8_t protocol, struct sockaddr *addr)
{
	struct iphdr	*ip;

	ip = (struct iphdr *)raw;
	ip->version = IPVERSION;
	ip->ihl = sizeof(struct iphdr) >> 2;
	ip->tos = 0;
	ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr));
	ip->id = htons(0);
	ip->frag_off = 0;
	ip->ttl = DEFAULT_TTL;
	ip->protocol = protocol;
	ip->saddr = ((struct sockaddr_in *)addr)->sin_addr.s_addr;
	ip->daddr = to->sin_addr.s_addr;
	ip->check = 0;
	ip->check = checksum((unsigned short *)ip, sizeof(*ip));
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

static void	set_tcp_pseudogram(char psg[], struct tcphdr *tcp, struct iphdr *ip)
{
	struct pseudo_header	*psh;

	psh = (struct pseudo_header *)psg;
	psh->source_address = ip->saddr;
	psh->dest_address = ip->daddr;
	psh->placeholder = 0;
	psh->protocol = IPPROTO_TCP;
	psh->length = htons(sizeof(struct tcphdr));
	ft_memcpy(psg + sizeof(*psh), tcp, sizeof(*tcp));
}

void			init_tcp_hdr(char raw[], t_data *data)
{
	struct tcphdr	*tcp;
	char			psg[sizeof(struct pseudo_header) + sizeof(struct tcphdr)];

	tcp = (struct tcphdr *)(raw + sizeof(struct iphdr));
	tcp->source = htons(data->id);
	tcp->dest = htons(data->port);
	tcp->seq = htonl(0);
	tcp->ack_seq = htonl(0);
	tcp->doff = 5; // 6
	tcp->res1 = 0;
	tcp->cwr = 0;
	tcp->ece = 0;
	tcp->urg = 0;
	tcp->ack = 0;
	tcp->psh = 0;
	tcp->rst = 0;
	tcp->syn = 0;
	tcp->fin = 0;
	tcp->window = htons(65535);
	tcp->check = 0;
	tcp->urg_ptr = htons(0);
	set_tcp_flags(tcp, data->scan);
	ft_memset(psg, 0, sizeof(psg));
	set_tcp_pseudogram(psg, tcp, (struct iphdr *)raw);
	tcp->check = checksum((unsigned short *)psg, sizeof(psg));
}
