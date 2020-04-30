
#include <arpa/inet.h>
#include <unistd.h>

#include "all.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_sprintf.h"

static void		printable_addr(int family, struct sockaddr *addr, char buf[], size_t size)
{
	if (!addr)
		return ;
	if (family == AF_INET)
		inet_ntop(AF_INET, &((struct sockaddr_in *)addr)->sin_addr, buf, size);
	else
		inet_ntop(AF_INET6, &((struct sockaddr_in6 *)addr)->sin6_addr, buf, size);
}

static void		printable_flags(char type[], int flags)
{
	if (flags & PCAP_IF_LOOPBACK)
		ft_strcpy(type, "loopback");
	else
		ft_strcpy(type, "ethernet");
}

static int		get_mask(struct sockaddr *netmask)
{
	char		*addr;
	int			mask;

	mask = 0;
	if (netmask->sa_family == AF_INET)
	{
		addr = (char *)&((struct sockaddr_in *)netmask)->sin_addr;
		for (u_int i = 0; i < sizeof(struct in_addr); i++)
			mask -= (addr[i] * 8);
	}
	else if (netmask->sa_family == AF_INET6)
	{
		addr = (char *)&((struct sockaddr_in6 *)netmask)->sin6_addr;
		for (u_int i = 0; i < sizeof(struct in6_addr); i++)
			mask -= (addr[i] * 8);
	}
	return (-mask);
}

static void		get_if_addrs(t_ifaddr **s, u_int bl[], t_params *e)
{
	pcap_if_t	*ptr;
	pcap_addr_t	*addr;
	t_ifaddr	**front;
	t_ifaddr	**end;

	*s = NULL;
	front = s;
	end = NULL;
	ptr = e->interfaces;
	while (ptr)
	{
		if (!(addr = ptr->addresses))
		{
			if (end == NULL)
				end = s;
			if (!(*end = ft_memalloc(sizeof(**end))))
				nmap_error(e, "Malloc t_ifaddr failed.");
			char *dup = ft_strjoin(ptr->name, ": ");
			if (!dup)
				nmap_error(e, "Malloc t_ifaddr->name failed.");
			(*end)->name = ft_strjoin(dup, ptr->description);
			free(dup);
			if (!(*end)->name)
				nmap_error(e, "Malloc t_ifaddr->name failed.");
			end = &(*end)->next;
		}
		while (addr)
		{
			if (addr->addr->sa_family == AF_INET || addr->addr->sa_family == AF_INET6)
			{
				t_ifaddr	*save = *front;
				char		ip[INET6_ADDRSTRLEN + 1];
				int			mask;

				if (!(*front = ft_memalloc(sizeof(**front))))
				{
					*front = save;
					nmap_error(e, "Malloc t_ifaddr failed.");
				}
				(*front)->name = ft_strdup(ptr->name);
				if (!(*front)->name)
				{
					*front = save;
					nmap_error(e, "Malloc t_ifaddr->name failed.");
				}
				bl[0] = (ft_strlen(ptr->name) > bl[0]) ? ft_strlen(ptr->name) : bl[0];
				printable_addr(addr->netmask->sa_family, addr->netmask, ip, sizeof(ip));
				printable_addr(addr->addr->sa_family, addr->addr, ip, sizeof(ip));
				mask = get_mask(addr->netmask);
				ft_sprintf((*front)->ip, "%s/%d", ip, -mask);
				bl[1] = (ft_strlen(ip) > bl[1]) ? ft_strlen((*front)->ip) : bl[1];
				printable_flags((*front)->type, ptr->flags);
				bl[2] = (ft_strlen((*front)->type) > bl[2]) ? ft_strlen((*front)->type) : bl[2];
				(*front)->flag = ptr->flags;
				(*front)->next = save;
				if (end == NULL)
					end = &(*front)->next;
			}
			else {
				char		ip[INET6_ADDRSTRLEN + 1];
				printable_addr(addr->addr->sa_family, addr->addr, ip, sizeof(ip));
				// ft_printf("%s %s\n", ptr->name, ip);
			}
			addr = addr->next;
		}
		ptr = ptr->next;
	}
}

static void		print_out(char *str, u_int len)
{
	int		slen;

	slen = len - ft_strlen(str);
	ft_printf("%s", str);
	while (slen-- >= 0)
		write(1, " ", 1);
}

static void print(pcap_if_t *all)
{
	char		ip[INET6_ADDRSTRLEN + 1];

	ft_printf("AF_INET: %d, AF_INET6:%d\n", AF_INET, AF_INET6);
	while (all)
	{
		ft_printf("%s %s %d:\n", all->name, all->description, all->flags);
		for (pcap_addr_t *addr = all->addresses; addr; addr = addr->next)
		{
			ft_printf("\tAddr : ");
			if (addr->addr)
			{
				printable_addr(addr->addr->sa_family, addr->addr, ip, sizeof(ip));
				ft_printf("%s (%d)\n\t", ip, addr->addr->sa_family);
				for (u_int i = 0; i < sizeof(addr->addr->sa_data); i++)
					ft_printf("%02X:", addr->addr->sa_data[i]);
			}
			ft_printf("\n");
			printable_addr(addr->addr->sa_family, addr->addr, ip, sizeof(ip));
			ft_printf("\tBroad: ");
			if (addr->broadaddr)
			{
				printable_addr(addr->broadaddr->sa_family, addr->broadaddr, ip, sizeof(ip));
				ft_printf("%s (%d)\n\t", ip, addr->broadaddr->sa_family);
				for (u_int i = 0; i < sizeof(addr->broadaddr->sa_data); i++)
					ft_printf("%02X:", addr->broadaddr->sa_data[i]);
			}
			ft_printf("\n");
			ft_printf("\tDest : ");
			if (addr->dstaddr)
			{
				printable_addr(addr->dstaddr->sa_family, addr->dstaddr, ip, sizeof(ip));
				ft_printf("%s (%d)\n\t", ip, addr->dstaddr->sa_family);
				for (u_int i = 0; i < sizeof(addr->dstaddr->sa_data); i++)
					ft_printf("%02X:", addr->dstaddr->sa_data[i]);
			}
			ft_printf("\n");
			ft_printf("\tNet  : ");
			if (addr->netmask)
			{
				printable_addr(addr->netmask->sa_family, addr->netmask, ip, sizeof(ip));
				ft_printf("%s (%d)\n\t", ip, addr->netmask->sa_family);
				get_mask(addr->netmask);
				// for (u_int i = 0; i < sizeof(addr->netmask->sa_data); i++)
				// 	ft_printf("%02X:", addr->netmask->sa_data[i]);
			}
			ft_printf("\n");
		}
		all = all->next;
	}
	ft_printf("\n");
}

char			**get_iflist_parameters(char **arg, t_params *e)
{
	t_ifaddr	*ptr;
	u_int		bl[3];

	bl[0] = 4; // "DEV "
	bl[1] = 8; // "IP/MASK "
	bl[2] = 5; // "TYPE "
if (0) print(e->interfaces);
	get_if_addrs(&e->ifaddrs, bl, e);
	ptr = e->ifaddrs;
	ft_printf("-------------------- INTERFACES --------------------\n");
	print_out("DEV ", bl[0]);
	print_out("IP/MASK ", bl[1]);
	print_out("TYPE ", bl[2]);
	write(1, "UP\n", 3);
	while (ptr && ptr->ip[0])
	{
		print_out(ptr->name, bl[0]);
		print_out(ptr->ip, bl[1]);
		print_out(ptr->type, bl[2]);
		ft_printf("%s\n", (ptr->flag & PCAP_IF_UP) ? "up" : "down");
		ptr = ptr->next;
	}
	ft_printf("\n");
	while (ptr)
	{
		ft_printf("%s\n", ptr->name);
		ptr = ptr->next;
	}
	ft_printf("\n");
	free_params(e);
	exit(0);
	return (arg);
}
