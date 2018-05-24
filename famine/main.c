/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:17:01 by root              #+#    #+#             */
/*   Updated: 2018/05/24 03:58:26 by root             ###   ########.fr       */
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

#define open 2
#define getdents64 217

struct linux_dirent64 {
	ino_t        d_ino;    /* 64-bit inode number */
	off_t        d_off;    /* 64-bit offset to next structure */
	unsigned short d_reclen; /* Size of this dirent */
	unsigned char  d_type;   /* File type */
	char           d_name[]; /* Filename (null-terminated) */
};

char		*direct[] = { "/tmp/test/", "/tmp/test2/", NULL };

int main()
{
	/* ft_printf("%x\n", O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC); */
	/* ft_printf("%d + %d = %d\n", sizeof(unsigned long), sizeof(unsigned short), sizeof(unsigned long) * 2 + sizeof(unsigned short)); */

	int		i;
	int		fd;
	char	buff[1024];
	int		ret;
	int		off;

	i = 0;
	while (direct[i])
	{
		memset(buff, 0, 1024);
		fd = syscall(open, direct[i], 0, 0);
		while ((ret = syscall(getdents64, fd, buff, 1024)) > 0)
		{
			off = 0;
			while (off < ret)
			{
				if (*(buff + off + 8+8+2) == DT_REG)
					ft_printf("%d %s\n", *(buff+off+8+8), buff + off + 8+8+2+1);
				off = off + *(buff + off + 16);
			}
		}
		close(fd);
		i++;
	}
	return 0;
}
