/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:13:10 by root              #+#    #+#             */
/*   Updated: 2018/06/28 08:21:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "durex.h"

static void			closeFileDescriptors(void)
{
	struct rlimit	lim;
	size_t			i;

	i = 3;
	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		return ;
	while (i < lim.rlim_max)
		close(i++);
}

static void			sanitizeEnvironment(void)
{
	extern char		**environ;

	for (int i = 0; environ && environ[i]; i++)
		memset(environ[i], 0, strlen(environ[i]));
}

int			main()
{
	t_env	e;

	if (setuid(getuid()) == -1)
		return (0);
	closeFileDescriptors();
	sanitizeEnvironment();
	e.lock = open(DUREX_LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (e.lock < 0)
		return (0);
	if (flock(e.lock, LOCK_EX | LOCK_NB))
		return (0);
	return (0);
}
