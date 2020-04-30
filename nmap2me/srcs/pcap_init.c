
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip6.h>
#include <netinet/ip.h>

#include "all.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_sprintf.h"

static int			islocalip(t_addr *addr, t_params *e)
{
	struct sockaddr_in		*sin;
	struct sockaddr_in6		*sin6;
	pcap_if_t				*ifs;
	pcap_addr_t				*addrs;
	char					ip[INET6_ADDRSTRLEN];
	int						family;

	if (addr->ptr->ai_family == AF_INET)
	{
		sin = (struct sockaddr_in *)addr->ptr->ai_addr;
		/* If it is 0.0.0.0 or starts with 127 then it is probably localhost. */
		if ((sin->sin_addr.s_addr & htonl(0xFF000000)) == htonl(0x7F000000))
			return (1);
		if (!sin->sin_addr.s_addr)
			return (1);
	}
	else
	{
		sin6 = (struct sockaddr_in6 *)addr->ptr->ai_addr;
		/* If it is ::0 or ::1 then it is probably localhost. */
		if (ft_memcmp(&(sin6->sin6_addr), "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16) == 0)
			return (1);
		if (ft_memcmp(&(sin6->sin6_addr), "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01", 16) == 0)
			return (1);
	}
	/* If it is the same addy as a local interface, then it is
		probably localhost */
	ifs = e->interfaces;
	while (ifs)
	{
		addrs = ifs->addresses;
		while (addrs)
		{
			if (addrs->addr)
			{
				family = addrs->addr->sa_family;
				if (family == AF_INET)
					inet_ntop(AF_INET, &((struct sockaddr_in *)addrs->addr)->sin_addr,
						ip, sizeof(ip));
				else if (family == AF_INET6)
					inet_ntop(AF_INET6, &((struct sockaddr_in6 *)addrs->addr)->sin6_addr,
						ip, sizeof(ip));
				else
					ip[0] = '\0';
				if (ft_strcmp(ip, addr->hostaddr) == 0)
					return (1);
			}
			addrs = addrs->next;
		}
		ifs = ifs->next;
	}
	/* OK, so to a first approximation, this addy is probably not
		localhost */
	return 0;
}

static char			*get_interface(t_addr *addr, t_params *e)
{
	pcap_if_t	*ifs;
	pcap_addr_t	*ads;
	int			islocal;

	ifs = e->interfaces;
	islocal = islocalip(addr, e);
	while (ifs)
	{
		if (e->device) // The user already specified a device
		{
			if (!ft_strcmp(e->device, ifs->name))
				break;
		}
		else if (ifs->flags & PCAP_IF_UP)
		{
			if (islocal && ifs->flags & PCAP_IF_LOOPBACK)
				break;
			if (!islocal)
				break;
		}
		ifs = ifs->next;
	}
	if (ifs)
	{
		ads = ifs->addresses;
		while (ads)
		{
			if (ads->addr && ads->addr->sa_family == AF_INET)
			{
				e->pcap.addr = ads->addr;
				inet_ntop(AF_INET, &((struct sockaddr_in *)ads->addr)->sin_addr,
					e->pcap.ip, sizeof(e->pcap.ip));
				return (ifs->name);
			}
			ads = ads->next;
		}
	}
	return (NULL);
}

void				init_pcap(t_addr *addr, t_params *e)
{
	char				*dev;
	char				errbuf[PCAP_ERRBUF_SIZE];
	char				filter_exp[1024];	/* The filter expression */
	struct bpf_program	fp;					/* Compiled filter version */
	bpf_u_int32			net;				/* The IP of our sniffing device */
	bpf_u_int32			mask;				/* The netmask of our sniffing device */

	if (!(dev = get_interface(addr, e)))
		nmap_error(e, "No interface found.");
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		ft_printf("WARNING: Can't get net/mask for device %s\n", errbuf);
		net = 0;
		mask = 0;
	}
	g_global.handle = pcap_open_live(dev, 4096, 1, -1, errbuf);
	if (g_global.handle == NULL)
		nmap_error(e, "ERROR: Couldn't open device %s\n", errbuf);
	ft_sprintf(filter_exp,
		"dst host %s and (icmp or ((tcp or udp or sctp) and (src host %s)))",
		e->pcap.ip,
		addr->hostaddr
	);
	if (e->debug)
		ft_printf("Packet capture filter (device %s): %s\n", dev, filter_exp);
	if (pcap_compile(g_global.handle, &fp, filter_exp, 1, mask) < 0)
		nmap_error(e, "ERROR: couldn't install filter %s: %s\n", filter_exp, pcap_geterr(g_global.handle));
	if (pcap_setfilter(g_global.handle, &fp) < 0)
		nmap_error(e, "ERROR: couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(g_global.handle));
	pcap_freecode(&fp);
	e->pcap.device = dev;
}
