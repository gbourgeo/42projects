#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <netinet/ip.h>
#include <arpa/inet.h>

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
	t_pcap 				*p = &globals.pcap;
	char 				err_buf[PCAP_ERRBUF_SIZE];

	ft_memset(p, 0, sizeof(*p));
	if ((p->device = pcap_lookupdev(err_buf)) == NULL) {
		ft_printf("%s\n", err_buf);
		return false;
	}
	if (pcap_lookupnet(p->device, &p->net, &p->mask, err_buf)) {
		ft_printf("Can't get netmask for device \"%s\": %s", p->device, err_buf);
		return false;
	}
	inet_ntop(AF_INET, (char*) &p->net, p->netstr, sizeof(p->netstr));
	inet_ntop(AF_INET, (char*) &p->mask, p->maskstr, sizeof(p->maskstr));
	p->handle = pcap_open_live(p->device, packet_size, promisc, timeout, err_buf);
	if (p->handle == NULL) {
		ft_printf("Couldn't open device \"%s\": %s\n", p->device, err_buf);
		return false;
	}
	if (pcap_datalink(p->handle) != DLT_EN10MB) {
		ft_printf("Device %s doesn't provide Ethernet headers - not supported\n", p->device);
		return false;
	}
	if (pcap_compile(p->handle, &p->fp, filter, 1, p->net)) {
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
	u_char 				l[] = "C'est moi";

	pcount = pcap_dispatch(p->handle, -1, handler, l);
	ft_printf("pcount=%d\n", pcount);
	if (pcount < 0)
		ft_printf("Error reading packets from interface \"%s\": %s", p->device, pcap_geterr(p->handle));
	pcap_close(p->handle);
	return true;
}