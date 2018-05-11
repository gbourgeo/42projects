/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/11 17:11:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "main.h"

static void		get_file_info(t_env *e)
{
	void		(*pack_elf[2])(t_env *) = { pack_elf32, pack_elf64 };
	Elf64_Ehdr	*file_header;
	
	file_header = (Elf64_Ehdr *)e->file;
	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type.", e);
	if (file_header->e_ident[EI_CLASS] == ELFCLASSNONE)
		ft_fatal("Unsupported ELF file class.", e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order.", e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", e);
	if (file_header->e_type != ET_EXEC)
		ft_fatal("Unsupported ELF file type.", e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", e);
	generate_new_key(e->key);
	pack_elf[file_header->e_ident[EI_CLASS] - 1](e);
}

int				main(int ac, char **av)
{
	t_env		e;

	ft_memset(&e, 0, sizeof(e));
	if (ac == 1) {
		ft_printf("usage: %s [program] <message>\n", av[0]);
		return (1);
	}
	e.progname = ft_strrchr(av[0], '/');
	e.progname = (e.progname == NULL) ? av[0] : e.progname + 1;
	e.banner = (av[2]) ? av[2] : "....WOODY....";
	if ((e.fd = open(av[1], O_RDWR)) == -1)
		ft_fatal(NULL, &e);
	if ((e.file_size = lseek(e.fd, 1, SEEK_END)) == -1)
		ft_fatal(NULL, &e);
	e.file = mmap(NULL, e.file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, e.fd, 0);
	if (e.file == MAP_FAILED)
		ft_fatal(NULL, &e);
	if (close(e.fd) == -1)
		perror("close()");
	e.fd = 0;

	get_file_info(&e);
	
	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}
