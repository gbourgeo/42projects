/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 23:53:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/07/15 02:49:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* remove */
#include <stdio.h>
/* exit */
#include <stdlib.h>

#include "main.h"

void			quitClearlyDaemon()
{
	if (e.child)
	{
		flock(e.lock, LOCK_UN);
		remove(DUREX_LOCK_FILE);
	}
	close(e.lock);
	exit(0);
}

void			daemonSigHandler(int sig)
{
	(void)sig;
	quitClearlyDaemon();
}
