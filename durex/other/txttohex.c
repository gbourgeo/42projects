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
	char buff[1];

	for ( int i = 1; av[i]; i++) {
		int fd = open(av[i], O_RDONLY);
		if (fd < 0) {
			printf("Convertig string '%s':\n", av[i]);
			for (int j = 0; av[i][j]; j++)
				printf("\\x%02x", av[i][j]);
		} else {
			printf("Convertig file '%s':\n", av[i]);
			while (read(fd, buff, 1) > 0)
				printf("\\x%02x", *buff);
			close(fd);
		}
		printf("\n\n");
	}
	return 0;
}
