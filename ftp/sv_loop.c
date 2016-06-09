/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 09:50:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int			check_end(int aff)
{
	int				ret;
	int				pid;

	while ((pid = wait4(0, &ret, WNOHANG, NULL)) > 0)
	{
		if (aff)
		{
			ft_putstr("\033[31mSERVEUR: Client pid=[\033[0m");
			ft_putnbr(pid);
			ft_putstr("\033[31m] killed.\n\033[0m");
		}
		return (-1);
	}
	return (0);
}

static void			aff_new_connect(struct sockaddr *sk, int ipversion)
{
	struct addrinfo	csin;

	ft_memset(&csin, 0, sizeof(csin));
	csin.ai_family = (ipversion == v6) ? AF_INET6 : AF_INET;
	csin.ai_addr = sk;
	ft_putstr("\033[32mSERVEUR: New connection: \033[0m");
	ft_aff_ip(&csin, ipversion);
	ft_putstr(" pid=");
}

static void			sv_accept(t_envi *sv, int version)
{
	int				count;
	int				fd;
	struct sockaddr	sk;
	socklen_t		len;

	count = 0;
	len = sizeof(sk);
	while ((fd = accept(sv->ip[version], &sk, &len)) > 0)
	{
		count += check_end(sv->success);
		if (sv->success)
			aff_new_connect(&sk, version);
		if (count < CLIENTS_MAX)
		{
			if (sv_launch_client(fd, sv) > 0)
				count++;
		}
		else
			send(fd, "Server full.", 12, 0);
		close(fd);
	}
	if (sv->success)
		ft_putendl_fd("\033[31mSERVEUR: accept(): Error", 2);
	close(sv->ip[version]);
}

void				sv_loop(t_envi *sv)
{
	pid_t			pid;

	if (sv->success)
		ft_putendl("\033[32mSERVEUR:\033[0m Waiting for clients...");
	pid = fork();
	if (pid > 0)
		sv_accept(sv, v4);
	else if (pid == 0)
		sv_accept(sv, v6);
	else
		ft_putendl_fd("\033[31mSERVEUR: fork() failed.", 2);
}
