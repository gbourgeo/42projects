#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <linux/if_arp.h>
#include <unistd.h>
#include <signal.h>

/*static void print_alldevices_information(pcap_if_t *alldevices)
{
	for (pcap_if_t *ptr = alldevices; ptr; ptr = ptr->next) {
		ft_printf("%s: %s ", alldevices->name, alldevices->description);
		if (alldevices->flags & PCAP_IF_LOOPBACK)
			ft_printf("LOOPBACK ");
		if (alldevices->flags & PCAP_IF_UP)
			ft_printf("UP ");
		if (alldevices->flags & PCAP_IF_RUNNING)
			ft_printf("RUNNING ");
		ft_printf("\n");
		for (pcap_addr_t *add = ptr->addresses; add; add = add->next) {

			char ipv[INET6_ADDRSTRLEN];
			socklen_t len;

			struct sockaddr *v4 = add->addr;
			if (v4) {
				if (v4->sa_family == AF_INET) {
					len = sizeof(struct sockaddr_in);
					if (!getnameinfo(v4, len, ipv, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST))
						ft_printf("\taddr: %s\n", ipv);
					else
						ft_printf("\taddr: error\n");
				}
				else if (v4->sa_family == AF_INET6) {
					len = sizeof(struct sockaddr_in6);
					if (!getnameinfo(v4, len, ipv, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST))
						ft_printf("\taddr: %s\n", ipv);
					else
						ft_printf("\taddr: error\n");
				}
				else if (v4->sa_family == AF_PACKET) {
					len = sizeof(struct sockaddr_ll);
					struct sockaddr_ll *p = (struct sockaddr_ll *)v4;
					ft_printf("\taddr: family %d proto %d index %d hatype %d pkttype %d halen %d addr %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
						p->sll_family, p->sll_protocol, p->sll_ifindex, p->sll_hatype, p->sll_pkttype, p->sll_halen,
						p->sll_addr[0], p->sll_addr[1], p->sll_addr[2], p->sll_addr[3], p->sll_addr[4], p->sll_addr[5]);
				}
			}
			v4 = add->netmask;
			if (v4) {
				if (v4->sa_family == AF_INET)
					len = sizeof(struct sockaddr_in);
				else if (v4->sa_family == AF_INET6)
					len = sizeof(struct sockaddr_in6);
				else if (v4->sa_family == AF_PACKET)
					len = sizeof(struct sockaddr_ll);
				if (!getnameinfo(v4, len, ipv, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST))
					ft_printf("\tnetmask: %s\n", ipv);
			}
			v4 = add->broadaddr;
			if (v4) {
				if (v4->sa_family == AF_INET)
					len = sizeof(struct sockaddr_in);
				else if (v4->sa_family == AF_INET6)
					len = sizeof(struct sockaddr_in6);
				else if (v4->sa_family == AF_PACKET)
					len = sizeof(struct sockaddr_ll);
				if (!getnameinfo(v4, len, ipv, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST))
					ft_printf("\tbroadaddr: %s\n", ipv);
			}
			v4 = add->dstaddr;
			if (v4) {
				if (v4->sa_family == AF_INET)
					len = sizeof(struct sockaddr_in);
				else if (v4->sa_family == AF_INET6)
					len = sizeof(struct sockaddr_in6);
				else if (v4->sa_family == AF_PACKET)
					len = sizeof(struct sockaddr_ll);
				if (!getnameinfo(v4, len, ipv, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST))
					ft_printf("\tdstaddr: %s\n", ipv);
			}
			ft_printf("\n");
		}
		ft_printf("\n");
	}	
}
*/

static void				pcap_free(t_pcap *p)
{
	if (p->device)
		free(p->device);
	if (p->handle)
		pcap_close(p->handle);
	ft_memset(p, 0, sizeof(p));
}

static void				pcap_alarm_breakloop()
{
	pcap_breakloop(globals.pcap.handle);
	alarm(0);
}

void 					pcap_dump(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data)
{
	static int			count = 0;
	struct ethhdr		*eth;

	(void)user;
	ft_printf("Packet %d received.\n", count + 1);
	ft_printf("Packet Header\n");
	ft_printf("\t|-Timevalue (seconds)  :%d\n", hdr->ts.tv_sec);
	ft_printf("\t|-Timevalue (mseconds) :%d\n", hdr->ts.tv_usec);
	ft_printf("\t|-Caplength            :%d\n", hdr->caplen);
	ft_printf("\t|-Length               :%d\n", hdr->len);
	eth = (struct ethhdr *)(data);
	ft_printf("Ethernet Header\n");
	ft_printf("\t|-Source          : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
	ft_printf("\t|-Destination     : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	ft_printf("\t|-Protocol        : %d\n", eth->h_proto);

	if (htons(eth->h_proto) == ETH_P_IP) {
		struct iphdr		*ip;
		struct sockaddr_in source;
		struct sockaddr_in dest;

		ip = (struct iphdr *)(data + sizeof(*eth));
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
	}
	ft_printf("\n");
	count++;
}

bool 					init_pcap(int packet_size, int promisc, int timeout, const char *filter)
{
	t_pcap 				*p 			= &globals.pcap;
	pcap_if_t 			*alldevices	= NULL;
	char 				err_buf[PCAP_ERRBUF_SIZE];
	struct sigaction 	alarm_breakloop;

	pcap_free(p);
	if (pcap_findalldevs(&alldevices, err_buf) == PCAP_ERROR) {
		ft_printf("%s\n", err_buf);
		return false;
	}
	if (alldevices == NULL) {
		ft_printf("Couldn't find any working device to capture network traffic.\n");
		return false;
	}
	p->device = ft_strdup(alldevices->name);
	for (pcap_addr_t *address = alldevices->addresses; address; address = address->next)
	{
		if (!address->addr)
			continue ;
		if (address->addr->sa_family == AF_PACKET) {
			struct sockaddr_ll *mac = (struct sockaddr_ll *)address->addr;

			ft_memcpy(&p->mac, mac, sizeof(p->mac));
		}
		else if (address->addr->sa_family == AF_INET) {
			struct sockaddr_in *v4 = (struct sockaddr_in *)address->addr;
			struct sockaddr_in *mask = (struct sockaddr_in *)address->netmask;

			ft_memcpy(&p->v4, v4, sizeof(p->v4));
			ft_memcpy(&p->net, &v4->sin_addr, sizeof(p->net));
			getnameinfo(address->addr, sizeof(*v4), p->netstr, INET_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
			ft_memcpy(&p->mask, &mask->sin_addr, sizeof(p->mask));
			getnameinfo(address->netmask, sizeof(*mask), p->maskstr, INET_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
		}
	}
	pcap_freealldevs(alldevices);
//	ft_printf("%s: addr %s, mask %s, mac %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", p->device, p->netstr, p->maskstr, p->mac.sll_addr[0], p->mac.sll_addr[1], p->mac.sll_addr[2], p->mac.sll_addr[3], p->mac.sll_addr[4], p->mac.sll_addr[5]);
	p->handle = pcap_open_live(p->device, packet_size, promisc, timeout, err_buf);
	if (p->handle == NULL) {
		ft_printf("Couldn't open device \"%s\": %s\n", p->device, err_buf);
		return false;
	}
	if (pcap_datalink(p->handle) != DLT_EN10MB) {
		ft_printf("Device %s doesn't provide Ethernet headers - not supported\n", p->device);
		return false;
	}
	if (pcap_compile(p->handle, &p->fp, filter, 0, p->net)) {
		ft_printf("Couldn't install filter \"%s\": %s\n", filter, pcap_geterr(p->handle));
		return false;
	}
	if (pcap_setfilter(p->handle, &p->fp)) {
		ft_printf("Couldn't parse filter \"%s\": %s\n", filter, pcap_geterr(p->handle));
		return false;
	}
	ft_memset (&alarm_breakloop, 0, sizeof(struct sigaction));
	alarm_breakloop.sa_sigaction = &pcap_alarm_breakloop;
	alarm_breakloop.sa_flags = SA_SIGINFO;
	if (sigaction(SIGALRM, &alarm_breakloop, NULL) < 0) {
		ft_printf("Couldn't set alarm handler.\n");
		return false;
	}
	p->timeout = timeout / 1000;
	return true;
}

bool 					launch_pcap(void (*handler)(u_char *, const struct pcap_pkthdr *, const u_char *))
{
	t_pcap 				*p = &globals.pcap;
	int 				pcount = 0;

	alarm(p->timeout);
	//	if (pcount == -2) pcap_breakloop was called.
	while (pcount != -2)
	{
		pcount = pcap_dispatch(p->handle, -1, handler, NULL);
		if (pcount == PCAP_ERROR)
			ft_printf("Error reading packets from interface \"%s\": %s\n", p->device, pcap_geterr(p->handle));
	}
	pcap_free(p);
	return true;
}