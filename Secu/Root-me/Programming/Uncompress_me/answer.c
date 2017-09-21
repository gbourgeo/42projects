/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 20:50:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/06/30 23:18:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "zlib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66

static const unsigned char d[] = {
    66,66,66,66,66,66,66,66,66,66,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,62,66,66,66,63,52,53,
    54,55,56,57,58,59,60,61,66,66,66,65,66,66,66, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,66,66,66,66,66,66,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66
};

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

static int base64decode(char *in, size_t inLen, unsigned char *out, size_t *outLen)
{
    char *end = in + inLen;
    char iter = 0;
    uint32_t buf = 0;
    size_t len = 0;
    
    while (in < end) {
        unsigned char c = d[*in++];
        switch (c) {
        case WHITESPACE: continue;   /* skip whitespace */
        case INVALID:    return 1;   /* invalid input, return error */
        case EQUALS:                 /* pad character, end of data */
            in = end;
            continue;
        default:
            buf = buf << 6 | c;
            iter++; // increment the number of iteration
            /* If the buffer is full, split it into bytes */
            if (iter == 4) {
                if ((len += 3) > *outLen) return 1; /* buffer overflow */
                *(out++) = (buf >> 16) & 255;
                *(out++) = (buf >> 8) & 255;
                *(out++) = buf & 255;
                buf = 0; iter = 0;
            }   
        }
    }
    if (iter == 3) {
        if ((len += 2) > *outLen) return 1; /* buffer overflow */
        *(out++) = (buf >> 10) & 255;
        *(out++) = (buf >> 2) & 255;
    }
    else if (iter == 2) {
        if (++len > *outLen) return 1; /* buffer overflow */
        *(out++) = (buf >> 4) & 255;
    }
    *outLen = len; /* modify to reflect the actual output size */
    return 0;
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
		strcpy(rep, "PRIVMSG Candy !ep4\n");
		write(1, rep, strlen(rep));
		write(fd, rep, strlen(rep));
		strcpy(rep + 18, " -rep ");
		while ((ret = read(fd, buff, 2048)) > 0)
		{
			write(1, buff, ret);
			buff[ret] = 0;
			if (strncmp(":Candy", buff, 6) == 0)
			{
				z_stream infstream;
				z_stream defstream;
				char *ptr = buff + 1;
				char stock[100];

				ptr = ft_strchr(ptr, ':') + 1;
				j = 100;
				base64decode(ptr, strlen(ptr), (unsigned char *)stock, &j);

				infstream.zalloc = Z_NULL;
				infstream.zfree = Z_NULL;
				infstream.opaque = Z_NULL;
				// setup "b" as the input and "c" as the compressed output
				infstream.avail_in = (uInt)(strlen(stock)); // size of input
				infstream.next_in = (Bytef *)stock; // input char array
				infstream.avail_out = (uInt)(26); // size of output
				infstream.next_out = (Bytef *)(rep + 24); // output char array
     
				// the actual DE-compression work.
				inflateInit(&infstream);
				inflate(&infstream, Z_NO_FLUSH);
				inflateEnd(&infstream);

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
