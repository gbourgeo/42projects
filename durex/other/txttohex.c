/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txttohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 21:19:30 by root              #+#    #+#             */
/*   Updated: 2018/08/12 21:24:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <unistd.h>

int main(int ac, char **av)
{
	for ( int i = 1; av[i]; i++) {
		printf("%s:\n", av[i]);
		int fd = open(av[i], O_RDONLY);
		if (fd < 0)
			continue ;
		char buff[1];
		while (read(fd, buff, 1) > 0)
			printf("\\x%02x", *buff);
		printf("\n\n");
		close(fd);
	}
	return 0;
}
