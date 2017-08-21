/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:35:30 by root              #+#    #+#             */
/*   Updated: 2017/08/21 14:37:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <stdlib.h>
#include <stdio.h>

static void		ft_ex_error(char *msg, int nb)
{
	if (!nb)
		fprintf(stderr, msg);
	else
		fprintf(stderr, msg, nb);
	fprintf(stderr, "\n");
	exit(2);
}

static void		ft_clean_env(void)
{
	if (e.outpack != NULL)
		free(e.outpack);
	if (e.probes != NULL)
		free(e.probes);
	ft_bzero(&e, sizeof(e));
	printf("\n");
}

static void		init_env(char *name)
{
	ft_memset(&e, 0, sizeof(e));
	e.prog = ft_strrchr(name, '/');
	e.prog = (e.prog == NULL ? name : e.prog + 1);
	e.module = DEFAULT;
	e.af = AF_UNSPEC;
	e.socktype = DEF_SOCKTYPE;
	e.protocol = DEF_PROTOCOL;
	e.first_hop = 1;
	e.max_hops = DEF_HOPS;
	e.sim_probes = DEF_SIM_PROBES;
	e.port = 0;
	e.wait_secs = DEF_WAIT_SEC;
	e.nprobes = DEF_PROBES;
	e.send_secs = DEF_SEND_SECS;
	e.packetlen = -1;
}

// 4fmNpwqzhIU
int				main(int ac, char **av)
{
	static void	(*ft_init[])(void) = { INIT_MODULE };

	init_env(av[0]);
	if (ac <= 1)
		ft_usage();
	if (ft_options(av))
		exit(2);
	if (setuid(getuid()) < 0)
		ft_err(e.prog, NULL);

	if (e.first_hop <= 0 || e.first_hop > e.max_hops)
		ft_ex_error("first hop out of range", 0);
	if (e.max_hops > MAX_HOPS)
		ft_ex_error("max hops cannot be more than %d", MAX_HOPS);
	if (e.nprobes <= 0 || e.nprobes > MAX_PROBES)
		ft_ex_error("no more than %d probes per hop", MAX_PROBES);
	if (e.wait_secs < 0)
		ft_ex_error("bad wait seconds `%g' specified\n", e.wait_secs);
	if (e.packetlen > MAX_DATALEN)
		ft_ex_error("too big packetlen %d specified", e.packetlen);
	if (e.send_secs < 0)
		ft_ex_error("bad sendtime `%g' specified", e.send_secs);
	if (e.send_secs >= 10)
		e.send_secs /= 1000;

	ft_getaddr();
	if (e.af == AF_INET6)
		ft_err(e.prog, "IP_V6 not supported");

	e.headerlen = sizeof(struct iphdr);
	ft_init[e.module]();
	ft_loop();
	ft_clean_env();
	return (0);
}
