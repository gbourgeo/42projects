/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 20:50:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/06/30 22:54:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int cl_init_addrinfo(char *ad, char *pt, struct addrinfo **res)
{
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	puts("\e[33mConnecting to \e[0m");
	puts(ad);
	puts("\e[33m on port \e[0m");
	puts(pt);
	puts("\e[33m...\e[0m");
	if (getaddrinfo(ad, pt, &hints, res))
		return (1);
	return (0);
}

static int get_info(char *addr, char *port, int *sock)
{
	struct addrinfo *results;
	struct addrinfo *tmp;

	if (cl_init_addrinfo(addr, port, &results))
		return (puts(" Failed"));
	tmp = results;
	while (tmp != NULL)
	{
		*sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (*sock == -1)
			continue ;
		if (connect(*sock, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		close(*sock);
		*sock = -1;
		tmp = tmp->ai_next;
	}
	freeaddrinfo(results);
	if (tmp == NULL)
		return (puts("No server found."));
	puts(" \e[32mOK\e[0m");
	return (0);
}

static char rot13(char c)
{
	if(c>='A' && c<='Z')
		return (c - 'A' + 13) % 26 + 'A';
	if(c>='a' && c<='z')
		return (c - 'a' + 13) % 26 + 'a';
	return c;
}

int main(void)
{
	int fd;
	char buff[2048];
	int ret;
	size_t j = 2048;

	memset(buff, 0, 2048);
	if (get_info("irc.root-me.org", "6667", &fd))
		return 1;
	ret = read(fd, buff, 2048);
	write(1, buff, ret);
	ret = read(fd, buff, 2048);
	write(1, buff, ret);
	write(1, "USER Q Q Q Q\n", 13);
	write(fd, "USER Q Q Q Q\n", 13);
	sleep(2);
	write(1, "NICK pury\n", 10);
	write(fd, "NICK pury\n", 10);
	while ((ret = read(fd, buff, 2048)) > 0)
	{
		write(1, buff, ret);
		if (ret < 2048)
			break;
	}
	sleep(2);
write(1, "JOIN\n", 5);
	write(fd, "JOIN #root-me_challenge\n", strlen("JOIN #root-me_challenge\n"));
	ret = read(fd, buff, 2048);
	write(1, buff, ret);
	sleep(2);
	while (ret > 0)
	{
		char rep[50];
		strcpy(rep, "PRIVMSG Candy !ep3\n");
		write(1, rep, strlen(rep));
		write(fd, rep, strlen(rep));
		strcpy(rep + 18, " -rep ");
		while ((ret = read(fd, buff, 2048)) > 0)
		{
			write(1, buff, ret);
			buff[ret] = 0;
			if (strncmp(":Candy", buff, 6) == 0)
			{
				char *ptr = buff + 1;
				ptr = ft_strchr(ptr, ':') + 1;
				int i = 24;
				while (ptr && *ptr) {
					write(1, ptr, 1);
					rep[i] = rot13(*ptr);
					i++;
					ptr++;
				}
				strcat(rep, "\n");
				write(1, rep, strlen(rep));
				write(fd, rep, strlen(rep));
				ret = read(fd, buff, 2048);
				write(1, buff, ret);
				ret = 0;
				break ;
			}
		}
		sleep(1);
	}
	write(1, "QUIT\n", 5);
	write(fd, "QUIT\n", 5);
	close(fd);
	return 0;
}
