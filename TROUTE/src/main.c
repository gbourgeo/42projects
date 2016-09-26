/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:35:30 by root              #+#    #+#             */
/*   Updated: 2016/09/26 17:08:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>
#include <stdio.h>

void			ft_usage(void)
{
	ft_putstr("Usage:\n  ");
	ft_putstr(e.prog);
	ft_putstr(" [ -4 ] [ -f first_ttl ] [ -m max_ttl ] [ -N squeries ]");
	ft_putstr(" [ -p port ] [ -w waittime ] [ -q nqueries ] [ -z sendwait ]");
	ft_putstr(" host [ packetlen ]\n");
	ft_putendl("  -4                          Use IPv4");
	ft_putendl("  -I                          Use ICMP ECHO for tracerouting");
	ft_putendl("  -f first_ttl                Start from the first_ttl hop (instead from 1)");
	ft_putendl("  -m max_ttl                  Set the max number of hops (max TTL to be");
	ft_putendl("                              reached). Default is 30");
	ft_putendl("  -N squeries                 Set the number of probes to be tried");
	ft_putendl("                              simultaneously (default is 16)");
	ft_putendl("  -p port                     Set the destination port to use. It is either");
	ft_putendl("                              initial udp port value for \"default\" method");
	ft_putstr("                              (incremented by each probe, default is ");
	ft_putnbr(DEF_START_PORT);
	ft_putendl(", or");
	ft_putendl("                              initial seq for \"icmp\" (incremented as well,");
	ft_putendl("                              default from 1), or some constant destination");
	ft_putendl("                              port for other methods (with default of 80 for");
	ft_putendl("                              \"tcp\", 53 for \"udp\", etc.)");
	ft_putendl("  -w waittime                 Set the number of seconds to wait for response to");
	ft_putendl("                              a probe (default is 5.0). Non-integer (float");
	ft_putendl("                              point) values allowed too");
	ft_putendl("  -q nqueries                 Set the number of probes per each hop. Default is");
	ft_putendl("                              3");
	ft_putendl("  -z sendwait                 Minimal time interval between probes (default 0).");
	ft_putendl("                              If the value is more than 10, then it specifies a");
	ft_putendl("                              number in milliseconds, else it is a number of");
	ft_putendl("                              seconds (float point values allowed too)");
	ft_putendl("  -U                          Use UDP to particular port for tracerouting");
	ft_putendl("                              (instead of increasing the port per each probe),");
	ft_putendl("                              default port is 53");
	ft_putendl("  -h                          Read this help and exit");
	ft_putendl("\nArguments:");
	ft_putendl("+     host          The host to traceroute to");
	ft_putendl("      packetlen     The full packet length (default is the length of an IP");
    ft_putendl("                    header plus 40). Can be ignored or increased to a minimal");
	ft_putendl("                    allowed value");
	exit(0);
}

static void		ft_ex_error(char *msg, int nb)
{
	if (!nb)
		fprintf(stderr, msg);
	else
		fprintf(stderr, msg, nb);
	fprintf(stderr, "\n");
	exit(2);
}

static void		ft_clean(void)
{
	if (e.outpack != NULL)
		free(e.outpack);
	if (e.probes != NULL)
		free(e.probes);
	ft_bzero(&e, sizeof(e));
	printf("\n");
}

// 4fmNpwqzhIU
int				main(int ac, char **av)
{
	static void	(*ft_init[])(void) = { ft_init_udp, ft_init_udp, ft_init_icmp };

	ft_memset(&e, 0, sizeof(e));
	e.prog = ft_strrchr(av[0], '/');
	e.prog = (e.prog == NULL) ? av[0] : e.prog + 1;
	e.module = DEFAULT;
	e.af = DEF_AF;
	e.socktype = DEF_SOCKTYPE;
	e.protocol = DEF_PROTOCOL;
	e.first_hop = 1;
	e.max_hops = DEF_HOPS;
	e.sim_probes = DEF_SIM_QUERIE;
	e.port = 0;
	e.wait = DEF_WAIT_SEC;
	e.nprobes = DEF_PROBES;
	e.send_secs = DEF_SEND_SECS;
	e.packetlen = -1;
	if (ac <= 1)
		ft_usage();
	if (ft_options(av))
		exit(2);
	if (e.first_hop <= 0 || e.first_hop > e.max_hops)
		ft_ex_error("first hop out of range", 0);
	if (e.max_hops > MAX_HOPS)
		ft_ex_error("max hops cannot be more than %d", MAX_HOPS);
	if (e.nprobes <= 0 || e.nprobes > MAX_PROBES)
		ft_ex_error("no more than %d probes per hop", MAX_PROBES);
	if (e.wait < 0)
	{
		fprintf(stderr, "bad wait seconds `%g' specified\n", e.wait);
		exit(2);
	}
	if (e.packetlen > MAX_DATALEN)
		ft_ex_error("too big packetlen %d specified", e.packetlen);
	if (e.send_secs < 0)
		ft_ex_error("bad sendtime `%g' specified", e.send_secs);
	if (e.send_secs >= 10)
		e.send_secs /= 1000;
	ft_getaddr();
	if (e.af == AF_INET6)
		ft_err(e.prog, "AF_INET6 not supported");
	e.headerlen = sizeof(struct iphdr);
	ft_init[e.module]();
	ft_loop();
	ft_clean();
	return (0);
}
