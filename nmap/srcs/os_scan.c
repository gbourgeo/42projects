/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_scan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 01:46:03 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/25 19:47:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void		set_pseudogram(char *pseudogram, struct pseudo_header *psh, struct tcphdr *header, int len, struct ip *ip_header, char *device)
{
	psh->source_address = inet_addr(device);
	psh->dest_address = ip_header->ip_dst.s_addr;
	psh->placeholder = 0;
	psh->protocol = IPPROTO_TCP;
	psh->length = htons(sizeof(struct tcphdr));
	ft_memset(pseudogram, 0, len);
	ft_memcpy(pseudogram, psh, sizeof(struct pseudo_header));
	ft_memcpy(pseudogram + sizeof(struct pseudo_header), header, sizeof(struct tcphdr));
}

static bool				tcp_header(BYTE *raw, int raw_len, char *device)
{
	struct tcphdr			header;
	struct pseudo_header	psh;
	struct ip				*ip_header = (struct ip*)((void*)raw);
	int						len = sizeof(struct pseudo_header) + sizeof(struct tcphdr);
	BYTE					pseudogram[len];

	header.source = htons(3389);
	header.dest = htons(3389);
	header.seq = htonl(1);
	header.ack_seq = 1;
	header.doff = 5;
	header.res1 = 0;
	header.cwr = 0;
	header.ece = 0;
	header.urg = 0;
	header.ack = 0;
	header.psh = 0;
	header.rst = 0;
	header.syn = 0;
	header.fin = 1;
	header.window = htons(5840);
	header.urg_ptr = 0;
	header.check = 0;
	set_pseudogram((char*)&pseudogram, &psh, &header, len, ip_header, device);
	header.check = checksum((unsigned short *)pseudogram, len);
	ft_memcpy((void*)raw + sizeof(struct ip), &header, sizeof(struct tcphdr));
	return true;
}

static bool			ipv4_header(BYTE *raw, int raw_len, char *host, u_char protocol, char *device)
{
	struct ip	header;
	header.ip_src.s_addr = inet_addr(device);
	if (!(inet_pton(AF_INET, host, &(header.ip_dst))))
	{
		printf("Can't set destination network address for %s\n", host);
		return false;
	}
	header.ip_ttl = DEFAULT_TTL;
	header.ip_p = protocol;
	header.ip_v = 4;
	header.ip_hl = sizeof(struct ip) >> 2;
	header.ip_tos = 0;
	header.ip_len = htons(raw_len);
	header.ip_off = 0;
	header.ip_id = htons(999);
	header.ip_sum = 0;
	header.ip_sum = checksum((unsigned short *) &header, sizeof(struct ip));
	ft_memcpy((void*)(raw), &header, sizeof(struct ip));
	return true;
}

static bool			send_to_socket(int fd, BYTE *raw, int raw_len)
{
	struct sockaddr_in		sin;
	struct ip				*ip_header = (struct ip*)((void*)raw);

	ft_memset (&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = ip_header->ip_dst.s_addr;
	sin.sin_port = htons(3389);
	return (sendto(fd, raw, raw_len, 0,
		(struct sockaddr *)&sin, sizeof(struct sockaddr)));
}

static void			recv_msg(int fd)
{
	char				buffer[ANSWER_BUFFER];
	struct				sockaddr_in from;
	socklen_t			len = sizeof(from);
	int					received = 0;

	received = recvfrom(fd, buffer, (ANSWER_BUFFER - 1), 0, (struct sockaddr*)&from, &len);
	if (received != SOCKET_ERROR) {
		struct ip				*ip_header		= (struct ip*)((void*)buffer);
		struct tcphdr			*tcp_header		= (struct tcphdr*)((void*)buffer + sizeof(struct ip));
		if (tcp_header->rst) {
			printf("OS: WINDOWS\n");
		} else {
			 printf("Unkown OS type\n");
		 }
	} else {
		printf("OS: UNIX (or cant guess)\n");
	}
}

static void			start_os_scan(char *address)
{
	int		fd					= 0;
	int		raw_len 			= sizeof(struct ip) + sizeof(struct tcphdr);
	BYTE	raw[raw_len];
	char	*default_interface 	= get_default_interface_host();

	if (!default_interface) { return; }
	if ((fd = init_socket(IPPROTO_TCP)) != SOCKET_ERROR) {
		printf("Initializing os scan... (%s)\n", address);
		if (ipv4_header((BYTE*)&raw, raw_len, address, IPPROTO_TCP, default_interface) &&
			tcp_header((BYTE*)&raw, raw_len, default_interface)) {
			if ((send_to_socket(fd, (BYTE*)&raw, raw_len)) > 0) {
				recv_msg(fd);
			}
		}
	}
}

static char			**get_host_addresses(struct hostent *host)
{
	char			**hosts		= NULL;
	struct in_addr	IP;
	int				i			= 0;
	int				len			= ft_array_len(host->h_addr_list) + 1;

	if (!(hosts = (char**)malloc(len * sizeof(char*))))
		return (NULL);
	i = 0;
	while (host->h_addr_list[i]) {
		IP.s_addr = *((uint32_t*) host->h_addr_list[i]);
		hosts[i++] = ft_strdup(inet_ntoa(IP));
	}
	hosts[i] = NULL;
	return (hosts);
}

void				init_os_scan(t_nmap *nmap)
{
	t_host			*hosts		= nmap->hosts;
	struct hostent	*host		= NULL;
	t_flag			*flag		= NULL;
	int				i			= 0;

	while (hosts)
	{
		if ((host = gethostbyname(hosts->address)) != NULL) {
			if (!hosts->addresses) {
				hosts->addresses = get_host_addresses(host);
			}
			if (hosts->addresses) {
				if ((flag = get_flag("deep")) != NULL) {
					while (hosts->addresses[i]) {
						start_os_scan(hosts->addresses[i++]);
					}
				} else if (hosts->addresses[0]) {
					start_os_scan(hosts->addresses[0]);
				}
			}
		} else {
			printf("Failed to resolve \"%s\".\n", hosts->address);
		}
		hosts = hosts->next;
	}
}
