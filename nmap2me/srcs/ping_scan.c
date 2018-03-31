#include <sys/types.h>	// *
#include <sys/socket.h> // socket()
#include <unistd.h>		// close()

#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_arp.h>
#include <linux/tcp.h>

#include <sys/ioctl.h>

#include "ft_printf.h"
#include "libft.h"
#include "all.h"

static bool				init_ping_scan(int *fds)
{	
	// Sending socket.
	fds[0] = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
	if (fds[0] < 0) {
		ft_printf("Failed to instantiate ping scan: `%s'\n", strerror(errno));
		return false;
	}

	// Receiving socket.
	fds[1] = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fds[1] < 0) {
		close(fds[0]);
		ft_printf("Failed to instantiate ping scan: `%s'\n", strerror(errno));
		return false;
	}

	return true;
}

static void				ping_scan_hosts(int *fds)
{
	struct sockaddr_ll 	to;
	static int 			port[] = { 0, 443, 80, 0 };
	int 				port_len = sizeof(port) / sizeof(*port);
	char 				*packet;
	int 				packet_len;

	ft_memset(&to, '\0', sizeof(to));
	to.sll_family = AF_PACKET;
	to.sll_ifindex = if_nametoindex(globals.pcap.device);
	ft_memset(to.sll_addr, 0xff, ETH_ALEN);
	to.sll_halen = ETH_ALEN;
	to.sll_protocol = htons(ETH_P_IP);

	packet = malloc(sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + 22);
	if (packet == NULL) {
		ft_printf("Can't send packet : insufficient memory.\n");
		return ;		
	}
	for (int i = 0; i < port_len; i++) {
		for (t_addr *address = globals.addresses; address != NULL; address = address->next) {
			if (address->error)
				continue ;
			packet_len = construct_packet(address, packet, port[i]);
			int ret = sendto(fds[0], packet, packet_len, 0, (struct sockaddr *)&to, sizeof(to));
			if (ret == -1) {
				ft_printf("send: %s\n", strerror(errno));
				continue ;
			}
		}
	}
/*
	for (int i = 0; i < port_len; i++) {
		t_addr *address = globals.addresses;
		while (address != NULL) {
			ft_memset(packet, 0, packet_len);
			int ret = recvfrom(fds[1], packet, packet_len, 0, NULL, NULL);
			if (ret == -1) {
				ft_printf("Recvfrom: %s\n", strerror(errno));
				continue ;
			}
			if (read_packet(packet, ret)) 
	 			address = address->next;
 		}
	}
*/
	free(packet);
}

void 				ping_scan()
{
	long 			hms;
	int 			fds[2];

	if (getuid() == 0) {

		gettimeofday(&globals.start, NULL);
		hms = globals.start.tv_sec % 86400;
		hms = (hms + 86400 + 3600) % 86400;
		ft_printf("\nInitiating Ping Scan at %d:%02d\n", hms / 3600, (hms % 3600) / 60);

		if (init_ping_scan(fds)) {

			if (globals.addresses_nb == 1)
				ft_printf("Scanning %s (%s) [4 ports]\n", globals.addresses[0].name, globals.addresses[0].hostaddr);
			else if (globals.addresses_nb > 1)
				ft_printf("Scanning %d hosts [4 ports/host]\n", globals.addresses_nb);

			ping_scan_hosts(fds);
			if (init_pcap(PACKET_SIZE, 1, 2000, "udp")) {
				launch_pcap(pcap_dump);
			}
			close(fds[0]);
			close(fds[1]);
		}
	}
	else
		ft_printf("Can't scan hosts. Update your privileges.\n");
}
