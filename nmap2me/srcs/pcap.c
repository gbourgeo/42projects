#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

static void print_alldevices_information(pcap_if_t *alldevices)
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
					/*struct sockaddr_ll
					  {
					    unsigned short int sll_family;
					    unsigned short int sll_protocol;
					    int sll_ifindex;
					    unsigned short int sll_hatype;
					    unsigned char sll_pkttype;
					    unsigned char sll_halen;
					    unsigned char sll_addr[8];
					  }; */
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

void 					pcap_dump(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data)
{
	static int			count = 0;

	data += 14; //link layer header
	struct ip 		*header = (struct ip *)data;
	ft_printf("user:%s ", user);
	ft_printf("timeval:%d,%d caplen:%d len:%d ", hdr->ts.tv_sec, hdr->ts.tv_usec, hdr->caplen, hdr->len);
	ft_printf("proto: %d ", header->ip_p);
	if (header->ip_p == IPPROTO_RAW) {
		ft_printf("IPPROTO_RAW ");
	}
	ft_printf("Packet %d received.\n", count);
	count++;
}

bool 					init_pcap(int packet_size, int promisc, int timeout, const char *filter)
{
	t_pcap 				*p 			= &globals.pcap;
	pcap_if_t 			*alldevices	= NULL;
	char 				err_buf[PCAP_ERRBUF_SIZE];

	if (p->device)
		free(p->device);
	ft_memset(p, 0, sizeof(*p));
	if (pcap_findalldevs(&alldevices, err_buf)) {
		ft_printf("%s\n", err_buf);
		return false;
	}
	if (alldevices == NULL) {
		ft_printf("Couldn't find any working device. Check your connection.\n");
		return false;
	}
	if (!packet_size)
		print_alldevices_information(alldevices);
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
			struct sockaddr_in *net = (struct sockaddr_in *)address->addr;
			struct sockaddr_in *mask = (struct sockaddr_in *)address->netmask;

			ft_memcpy(&p->v4, v4, sizeof(p->v4));
			ft_memcpy(&p->net, &net->sin_addr, sizeof(p->net));
			getnameinfo(address->addr, sizeof(*net), p->netstr, INET_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
			ft_memcpy(&p->mask, &mask->sin_addr, sizeof(p->mask));
			getnameinfo(address->netmask, sizeof(*mask), p->maskstr, INET_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
		}
	}
	pcap_freealldevs(alldevices);
	ft_printf("%s: %s %s\n", p->device, p->netstr, p->maskstr);
/*	if (pcap_lookupnet(p->device, &p->net, &p->mask, err_buf)) {
		ft_printf("Can't get netmask for device \"%s\": %s", p->device, err_buf);
		return false;
	}
	inet_ntop(AF_INET, (char*) &p->net, p->netstr, sizeof(p->netstr));
	inet_ntop(AF_INET, (char*) &p->mask, p->maskstr, sizeof(p->maskstr));
	ft_printf("2:%s %s\n", p->netstr, p->maskstr);
*/	p->handle = pcap_open_live(p->device, packet_size, promisc, timeout, err_buf);
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
	return true;
}

bool 					launch_pcap(void (*handler)(u_char *, const struct pcap_pkthdr *, const u_char *))
{
	t_pcap 				*p = &globals.pcap;
	int 				pcount;
	u_char 				l[] = "HI";

	pcount = pcap_dispatch(p->handle, -1, handler, l);
	ft_printf("pcount=%d\n", pcount);
	if (pcount < 0)
		ft_printf("Error reading packets from interface \"%s\": %s", p->device, pcap_geterr(p->handle));
	pcap_close(p->handle);
	return true;
}