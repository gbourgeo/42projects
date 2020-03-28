
#include "all.h"
#include "libft.h"

#include <errno.h>
#include <string.h>
#include <net/if.h>

void 				get_interface(t_params *e)
{
	struct ifaddrs 	*ifs, *ifa;

	ifs = NULL;
	errno = 0;
	if (getifaddrs(&ifs))
		nmap_error(e, "%s.", strerror(errno));
	for (ifa = ifs; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr
			&& ifa->ifa_addr->sa_family == AF_INET
			&& (ifa->ifa_flags & (IFF_BROADCAST)))
		{
			e->device = ft_strdup(ifa->ifa_name);
			break ;
		}
	}
	freeifaddrs(ifs);
	if (ifa == NULL)
		nmap_error(e, "No interface found.");
}
