/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:51:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 14:03:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"
#include "ft_printf.h"
#include "libft.h"
#include "main.h"

int				ft_fatal(char *str, t_env *e)
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

	if (ac == 1) {
		ft_fprintf(stderr, "usage: %s [program]\n", av[0]);
		return (1);
	}
	ft_memset(&e, 0, sizeof(e));
	e.progname = ft_strrchr(av[0], '/');
	e.progname = (e.progname == NULL) ? av[0] : e.progname + 1;
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

#ifdef __APPLE__
	pack_macho(&e);
#elif defined _WIN32 || defined _WIN64
	pack_pe(&e);
#else
	pack_elf(&e);
#endif

	if (munmap(e.file, e.file_size) == -1)
		ft_fatal(NULL, &e);
	return (0);
}
