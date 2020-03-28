
#include "all.h"
#include "libft.h"
#include "ft_printf.h"

#include <netinet/ip.h>
#include <linux/tcp.h>
#include <arpa/inet.h>

void			pcap_dump(
unsigned char *user,
const struct pcap_pkthdr *h,
const unsigned char *bytes
)
{
	struct ip	*header;
    static int	count = 1;
	int			i;
	
	i = 0;
	// bytes += 14; // link layer header
	header = (struct ip *)(bytes + 14); // link layer header
	if (header->ip_p == IPPROTO_TCP)
	{
		struct tcphdr	*tcp_header;
		int				id;

		tcp_header = (struct tcphdr*)((void *)header + sizeof(struct ip));
		id = ntohs(tcp_header->dest);
		// t_queue *queue = find_queue(IPPROTO_TCP, id);
		// if (queue) {
		// 	if (!ft_strcmp(queue->scan, "SYN") && tcp_header->syn) {
		// 		if (tcp_header->ack) {
		// 			queue->open = true;
		// 			queue->filtered = false;
		// 		}
		// 		else if (tcp_header->rst)
		// 			queue->filtered = true;
		// 	} else if (!ft_strcmp(queue->scan, "ACK") && tcp_header->rst) {
		// 		queue->filtered = false;
		// 	} else if (!ft_strcmp(queue->scan, "FIN") && tcp_header->rst) {
		// 		queue->open = false;
		// 	} else if (!ft_strcmp(queue->scan, "NULL") && tcp_header->rst && tcp_header->ack) {
		// 		queue->open = false;
		// 	} else if (!ft_strcmp(queue->scan, "XMAS") && tcp_header->rst && tcp_header->ack) {
		// 		queue->open = false;
		// 	}
		// 	queue->done = true;
		// }
	}
	else if (header->ip_p == IPPROTO_ICMP)
	{
		struct ip		*ip_header;

		ip_header = (struct ip *)((void*)header);
		// t_queue *queue = find_queue(IPPROTO_UDP, -1);
		// if (queue) {
		// 	queue->open = false;
		// 	queue->filtered = false;
		// 	queue->done = true;
		// }
	}
    // fflush(stdout);
    count++;
}

void				init_pcap(t_params *e)
{
	char				*dev;
	char				errbuf[PCAP_ERRBUF_SIZE];
	struct bpf_program	fp;					/* The compiled filter expression */
	char				netstr[INET_ADDRSTRLEN];
	char				maskstr[INET_ADDRSTRLEN];
	char				filter_exp[256];	/* The filter expression */
	bpf_u_int32			mask;				/* The netmask of our sniffing device */
	bpf_u_int32			net;				/* The IP of our sniffing device */

	dev = e->device;
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		ft_printf("WARNING: Can't get net/mask for device %s\n", errbuf);
		net = 0;
		mask = 0;
	}
	e->handle = pcap_open_live(dev, 4096, 1, e->pcap_timeout, errbuf);
	if (e->handle == NULL)
		nmap_error(e, "ERROR: Couldn't open device %s\n", errbuf);
	inet_ntop(AF_INET, (char*) &net, netstr, sizeof (netstr));
	inet_ntop(AF_INET, (char*) &mask, maskstr, sizeof (maskstr));
	ft_strncpy(filter_exp, "tcp or udp or icmp", sizeof(filter_exp));
	if (pcap_compile(e->handle, &fp, filter_exp, 1, mask) < 0)
		nmap_error(e, "ERROR: couldn't install filter %s: %s\n", filter_exp, pcap_geterr(e->handle));
	if (pcap_setfilter(e->handle, &fp) < 0)
		nmap_error(e, "ERROR: couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(e->handle));
	if (pcap_dispatch(e->handle, -1, pcap_dump, NULL) < 0)
		nmap_error(e, "ERROR: error reading packets from interface %s: %s", dev, pcap_geterr(e->handle));
	pcap_close(e->handle);
	pcap_freecode(&fp);
	e->handle = NULL;
}