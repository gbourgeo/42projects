/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:17:01 by root              #+#    #+#             */
/*   Updated: 2018/05/27 01:59:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_printf.h"

#define OPEN		2
#define GETDENTS64	217
#define LSEEK		8
#define MMAP		9
#define MUNMAP		11

struct linux_dirent64 {
	ino_t        d_ino;    /* 64-bit inode number */
	off_t        d_off;    /* 64-bit offset to next structure */
	unsigned short d_reclen; /* Size of this dirent */
	unsigned char  d_type;   /* File type */
	char           d_name[]; /* Filename (null-terminated) */
};

char		*direct[] = { "/tmp/test/", "/tmp/test2/", NULL };

void	find_files(char *dir);
void	get_dat_elf(char *dir, char *file);
void	pack_dat_elf(int fd, int size, char *data);

int main(int ac, char **av)
{
	/* ft_printf("%x\n", O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC); */
	/* ft_printf("%d + %d = %d\n", sizeof(unsigned long), sizeof(unsigned short), sizeof(unsigned long) * 2 + sizeof(unsigned short)); */
	find_files(direct[0]);
	find_files(direct[1]);
	return 0;
}

void	find_files(char *dir)
{
	int		fd;
	char	buff[1024];
	int		ret;
	int		off;
	
	fd = syscall(OPEN, dir, 0, 0);
	if (fd == -1)
		return ;
	while ((ret = syscall(GETDENTS64, fd, buff, 1024)) > 0)
	{
		off = 0;
		while (off < ret)
		{
			if (*(buff + off + 8+8+2) == DT_REG)
				get_dat_elf(dir, buff + off + 8 + 8 + 2 + 1);
			off = off + *(buff + off + 16);
		}
	}
	close(fd);
}

void	get_dat_elf(char *dir, char *file)
{
	char	path[1024];
	int		fd;
	int		size;
	void	*data;
	int		i;
	int		j;

	i = 0;
	while (dir[i])
	{
		path[i] = dir[i];
		i++;
	}
	j = 0;
	while (file[j])
	{
		path[i + j] = file[j];
		j++;
	}
	path[i + j] = '\0';
	fd = syscall(OPEN, path, 0, 0);
	if (fd == -1)
		return ;
	size = syscall(LSEEK, fd, 1, SEEK_END);
	if (size == -1)
	{
		close(fd);
		return ;
	}
	data = (void *)syscall(MMAP, NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED)
	{
		close(fd);
		return ;
	}
	printf("%s ", path);
	pack_dat_elf(fd, size, data);
	close(fd);
	syscall(MUNMAP, data, size);
}

void		pack_dat_elf(int fd, int size, char *data)
{
	if (data[0] == 0x7f && data[1] == 'E' && data[2] == 'L' && data[3] == 'F'	&&
		data[4] == 2 && data[5] != 0 && data[6] == 1 && (data[16] == 2 || data[16] == 3))
		// Ajouter le check de signature de binaire
	{
		printf("%s %d %d\n", data, fd, size);
	}
	else
		printf("not en elf file\n");
}
