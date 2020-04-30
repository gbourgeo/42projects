
#include <arpa/inet.h>

#include "all.h"
#include "ft_printf.h"
#include "ft_sprintf.h"
#include "libft.h"

static void		print_addrs(char *name, struct addrinfo *addr, char unique[])
{
	char		hostaddr[INET6_ADDRSTRLEN];

	ft_printf("Other addresses for %s (not scanned):", name);
	while (addr)
	{
		if (addr->ai_family == AF_INET)
			inet_ntop(addr->ai_family,
				&((struct sockaddr_in *)addr->ai_addr)->sin_addr,
				hostaddr, sizeof(hostaddr));
		else if (addr->ai_family == AF_INET6)
			inet_ntop(addr->ai_family,
				&((struct sockaddr_in6 *)addr->ai_addr)->sin6_addr,
				hostaddr, sizeof(hostaddr));
		if (ft_strcmp(hostaddr, unique))
			ft_printf(" %s", hostaddr);
		addr = addr->ai_next;
	}
	ft_printf("\n");
}

static char		*get_status(t_response *r)
{
	if (r->open)
		return ("open");
	if (r->filtered)
		return ("filtered");
	return ("closed");
}

static char		*get_port_scan(int port, char *scan)
{
	static char		tbuf[16];

	ft_sprintf(tbuf, "%d/%s", port, (!ft_strcmp(scan, "UDP")) ? "udp" : "tcp");
	return (tbuf);
}

static char		*get_reason(t_response *r)
{
	static char		tbuf[128];

	if (r->received == 0)
		return ("no-response");
	if (r->open)
	{
		struct iphdr	*ip = (struct iphdr *)r->raw;
		struct tcphdr *tcp = (struct tcphdr *)(ip + 1);
		struct { int data; char *name; } data[] = {
			{ tcp->fin, "fin" },
			{ tcp->syn, "syn" },
			{ tcp->rst, "rst" },
			{ tcp->psh, "psh" },
			{ tcp->ack, "ack" },
			{ tcp->urg, "urg" },
			{ tcp->ece, "ece" },
			{ tcp->cwr, "cwr" },
		};

		tbuf[0] = 0;
		for (unsigned int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
			if (data[i].data)
			{
				ft_strcat(tbuf, data[i].name);
				ft_strcat(tbuf, " ");
			}
		ft_sprintf(tbuf + ft_strlen(tbuf), "ttl %d", ip->ttl);
		return (tbuf);
	}
	return ("close");
}

void			scan_report(t_addr *addr, t_params *e)
{
	unsigned int	opes;
	unsigned int	i;

	opes = e->ports_nb * e->scans_nb;
	i = 0;
	ft_printf("%s scan report for %s (%s)\n", e->progname, addr->name, addr->hostaddr);
	if (addr->addrnb > 1)
		print_addrs(addr->name, addr->res, addr->hostaddr);
	if (e->debug)
	{
		ft_printf("Scanned at %s for ", get_time("%Y-%m-%d %H:%M:%S %Z", &e->start_time));
		if (e->tcp_timeout / 1000 > 0)
			ft_printf("%ds\n", e->tcp_timeout / 1000 * e->retry);
		else
			ft_printf("%dms\n", e->tcp_timeout * e->retry);
	}
	ft_printf("%-9s %-8s ", "PORT", "STATE");
	if (e->verbose || e->debug)
		ft_printf("REASON");
	ft_printf("\n");
	if (opes <= 30)
	{
		while (i < opes)
		{
			ft_printf("%-9s %-8s",
				get_port_scan(e->data[i].port, e->data[i].scan),
				get_status(&e->data[i].response));
			if (e->verbose || e->debug)
				ft_printf(" %s", get_reason(&e->data[i].response));
			ft_printf("\n");
			i++;
		}
	}
	else
	{
		int closed = 0;
		int filtered = 0;
		while (i < opes)
		{
			if (e->data[i].response.received && e->data[i].response.open)
			{
				ft_printf("%-9s %-8s",
					get_port_scan(e->data[i].port, e->data[i].scan),
					get_status(&e->data[i].response));
				if (e->verbose || e->debug)
					ft_printf(" %s", get_reason(&e->data[i].response));
				ft_printf("\n");
			}
			else if (!ft_strcmp(e->data[i].scan, "UDP"))
			{

			}
			else
			{
				if (e->data[i].response.filtered)
					filtered++;
				else
					closed++;
			}
			i++;
		}
		if (closed)
			ft_printf("\nNot shown: %d closed ports\n", closed);
		if (filtered)
			ft_printf("\nNot shown: %d filtered ports\n", filtered);
	}
}
