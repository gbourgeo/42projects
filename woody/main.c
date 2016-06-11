/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/11 12:27:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int				ft_usage(char *name)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" [program]", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int				ft_error(char *str, int error, t_env *e)
{
	ft_putstr_fd("Error: ", 2);
	if (error)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	if (e->fd)
		close(e->fd);
	if (e->file)
		munmap(e->file, e->file_size);
	return (1);
}

int				main(int ac, char **av)
{
	t_env		e;
	Elf64_Ehdr	*hdr;

	if (ac == 1)
		return (ft_usage(av[0]));
	ft_memset(&e, 0, sizeof(e));
	if ((e.fd = open(av[1], O_RDONLY)) == -1)
		return (ft_error("open()", 1, &e));
	if ((e.file_size = lseek(e.fd, 1, SEEK_END)) == -1)
		return (ft_error("lseek()", 1, &e));
	e.file = mmap(NULL, e.file_size, PROT_READ, MAP_PRIVATE, e.fd, 0);
	if (e.file == MAP_FAILED)
		return (ft_error("mmap()", 1, &e));
	if (close(e.fd) == -1)
		ft_error("close()", 1, &e);
/* 	magic = *(uint32_t *)e.file; */
/* 	if (magic != MH_MAGIC_64 && magic != MH_CIGAM_64) */
	hdr = (Elf64_Ehdr *)e.file;
	ft_putnbr(*(int *)e.file);write(1, " ", 1);
	ft_putnbr('\x7f');write(1, "\n", 1);
	if (hdr->e_ident[0] != '\x7f')
		return (ft_error("File architecture not suported. x86_64 only", 0, &e));
	if (munmap(e.file, e.file_size) == -1)
		return (ft_error("munmap()", 1, &e));
	return (0);
}
