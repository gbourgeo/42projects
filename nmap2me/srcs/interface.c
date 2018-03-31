#include "all.h"
#include "ft_printf.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

void 				get_hosts_addr()
{
	struct hostent	*host;
	struct in_addr	ip;

	for (t_addr *ptr = globals.addresses; ptr != NULL; ptr = ptr->next) {
		host = gethostbyname(ptr->name);
		ip.s_addr = (host) ? *((uint32_t *)host->h_addr_list[0]) : inet_addr(ptr->name);
		if (ip.s_addr != INADDR_NONE)
			ft_memcpy(ptr->hostaddr, inet_ntoa(ip), sizeof(ptr->hostaddr));
		else {
			ptr->error = hstrerror(h_errno);
			ft_printf("Failed to resolve \"%s\": %s\n", ptr->name, ptr->error);
			globals.addresses_nb--;
		}
	}
}

void 				get_interface()
{
	struct ifaddrs 	*ifs, *ifa;

	ifs = NULL;
	if (getifaddrs(&ifs))
		nmap_error("%s: Interfaces : %s", globals.progname, strerror(errno));
	for (ifa = ifs; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && (ifa->ifa_flags & (IFF_BROADCAST))) {
			ft_memcpy(&globals.interface, ifa, sizeof(*ifa));
			break ;
		}
	}
	if (ifa == NULL)
		nmap_error("%s: No valid interface found.", globals.progname);
//	ft_printf("\tinterface: %s", globals.interface.ifa_name);
	freeifaddrs(ifs);
}
