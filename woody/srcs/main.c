/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/19 17:08:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include "libft.h"
#include "main.h"

void					file_info(t_env *e);

static int				ft_fatal(char *str, t_env *e)
{
	ft_fprintf(stderr, "%s: ", e->progname);
	if (!str)
		perror(str);
	else
		ft_fprintf(stderr, "%s\n", str);
	if (e->fd > 0)
		close(e->fd);
	if (e->file != NULL)
		munmap(e->file, e->file_size);
	exit(1);
}

int				main(int ac, char **av)
{
	t_env		e;
	Elf64_Ehdr	*file_header;

	if (ac == 1) {
		ft_fprintf(stderr, "usage: %s [program]\n", av[0]);
		return (1);
	}
	ft_memset(&e, 0, sizeof(e));
	e.progname = ft_strrchr(av[0], '/');
	e.progname = (e.progname == NULL) ? av[0] : e.progname + 1;
	if ((e.fd = open(av[1], O_RDONLY)) == -1)
		ft_fatal(NULL, &e);
	if ((e.file_size = lseek(e.fd, 1, SEEK_END)) == -1)
		ft_fatal(NULL, &e);
	e.file = mmap(NULL, e.file_size, PROT_READ, MAP_PRIVATE, e.fd, 0);
	if (e.file == MAP_FAILED)
		ft_fatal(NULL, &e);
	if (close(e.fd) == -1)
		perror("close()");
	e.fd = 0;

	file_header = (Elf64_Ehdr *)e.file;
	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type.", &e);
	if (file_header->e_ident[EI_CLASS] != ELFCLASS64)
		ft_fatal("Unsupported ELF file class.", &e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order.", &e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", &e);
	if (file_header->e_type != ET_EXEC)
		ft_fatal("Unsupported ELF file type.", &e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", &e);

	file_info(&e);

	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}
