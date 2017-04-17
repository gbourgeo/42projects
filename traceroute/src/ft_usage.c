/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 00:00:09 by root              #+#    #+#             */
/*   Updated: 2017/04/18 00:00:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
