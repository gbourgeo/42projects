/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:17:01 by root              #+#    #+#             */
/*   Updated: 2018/05/23 04:44:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_printf.h"

#define getdents64 78

struct linux_dirent {
	unsigned long  d_ino;     /* Inode number */
	unsigned long  d_off;     /* Offset to next linux_dirent */
	unsigned short d_reclen;  /* Length of this linux_dirent */
	char           d_name[];  /* Filename (null-terminated) */
	/* length is actually (d_reclen - 2 -
	   offsetof(struct linux_dirent, d_name)) */
	/*
               char           pad;       // Zero padding byte
               char           d_type;    // File type (only since Linux
                                         // 2.6.4); offset is (d_reclen - 1)
										 */
};

char		*direct[] = { "/tmp/test/", "/tmp/test2/", NULL };

int main()
{
	/* ft_printf("%x\n", O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC); */
	/* ft_printf("%d + %d = %d\n", sizeof(unsigned long), sizeof(unsigned short), sizeof(unsigned long) * 2 + sizeof(unsigned short)); */

	int		i;
	int		fd;
	char	buff[1024];
	struct linux_dirent *dir;
	int		ret;
	int		off;

	i = 0;
	while (direct[i])
	{
		memset(buff, 0, 1024);
		fd = open(direct[i], O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC);
		while ((ret = syscall(getdents64, fd, buff, 1024)) > 0)
		{
			dir = (struct linux_dirent *)buff;
			off = 0;
			while (off < ret)
			{
				ft_printf("%s\n", dir->d_name);
				off += dir->d_reclen;
				dir = (struct linux_dirent *)(buff + off);
			}
		}
		close(fd);
		i++;
	}
	return 0;
}
