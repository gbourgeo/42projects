/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:27:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/14 09:13:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"
#include "main.h"

void			pack_macho32(t_env *e);
void			pack_macho64(t_env *e);
extern uint32_t	woody64_size;
void			woody64_encrypt(u_char *data, size_t len, const uint32_t *key);
void			woody64_func(void);
void			woody64_decrypt(u_char *data, size_t len, const uint32_t *key);
void			print_hex(u_char *data, uint32_t size);
void			print_macho64(t_env *e);

static int		is_macho(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}	

static int		is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

static int		is_swap(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_MAGIC_64);
}

void			get_macho_info(t_env *e)
{
	struct mach_header	*header;
	uint32_t			magic;

	header = (struct mach_header *)e->file;
	magic = header->magic;
	if (!is_macho(magic))
		ft_fatal("Invalid MACHO file type", e);
	if (header->filetype != MH_EXECUTE)
		ft_fatal("Unsupported MACHO file type", e);

	is_64(magic) ? pack_macho64(e) : pack_macho32(e);
}

void			pack_macho32(t_env *e)
{
	struct mach_header_64		*header;
	uint32_t					offset;

	header = (struct mach_header_64 *)e->file;
	offset = sizeof(*header);

	struct load_command			*cmd;
	char						maxprot[]  = "(   )";
	char						initprot[] = "(   )";
	ft_printf("\ncmd\t\t cmdsize\t segname\t vmaddr\t\t vmsize\t fileoff\t filesize\t maxprot\t initprot\t nsects\t flags\n");
	for (size_t i = 0; i < header->ncmds; i++)
	{
		cmd = (struct load_command *)(e->file + offset);
		if (cmd->cmd == LC_SEGMENT)
		{
			struct segment_command *segment = (struct segment_command *)cmd;
			ft_printf("%-11d\t %#.5x\t %-11s\t %-11p\t %#x\t %#-5x\t\t %#-5x\t\t %d %s\t %d %s\t %-5d\t %#x\n",
					  segment->cmd, segment->cmdsize, segment->segname, segment->vmaddr,
					  segment->vmsize, segment->fileoff, segment->filesize, segment->maxprot, maxprot,
					  segment->initprot, initprot, segment->nsects, segment->flags);
		}
		else
			ft_printf("%-11d\t %#.5x\n", cmd->cmd, cmd->cmdsize);
		offset += cmd->cmdsize;
	}
}

void			pack_macho64(t_env *e)
{
	struct mach_header_64		*header;
	uint32_t					offset;
	struct load_command			*cmd;
	struct segment_command_64	*segment;
	struct segment_command_64	*segtext;
	struct entry_point_command	*entry;
	struct section_64			*section;
	struct section_64			*sectext;
	struct section_64			*lastsec;

	header = (struct mach_header_64 *)e->file;
	offset = sizeof(*header);
	for (size_t i = 0; i < header->ncmds; i++)
	{
		cmd = (struct load_command *)(e->file + offset);
		if (cmd->cmd == LC_MAIN)
			entry = (struct entry_point_command *)cmd; /* Get the program entry point */
		else if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if (ft_strcmp(segment->segname, SEG_TEXT) == 0)
			{
				segtext = segment; /* Get the __TEXT segment */
				section = (struct section_64 *)(segment + 1);
				for (size_t j = 0; j < segment->nsects; j++)
				{
					if (ft_strcmp(section[j].sectname, SECT_TEXT) == 0)
						sectext = section; /* Get the __text section */
					if (j + 1 == segment->nsects)
						lastsec = section;
				}
			}
		}
		offset += cmd->cmdsize;
	}
	print_macho64(e);
	print_hex((u_char *)(e->file + sectext->offset), sectext->size);
	woody64_encrypt((u_char *)(e->file + sectext->offset), sectext->size, e->key);
	print_hex((u_char *)(e->file + sectext->offset), sectext->size);
	woody64_decrypt((u_char *)(e->file + sectext->offset), sectext->size, e->key);
	print_hex((u_char *)(e->file + sectext->offset), sectext->size);

	entry->entryoff = lastsec->offset + lastsec->size;
	lastsec->size += woody64_size;
//	segtext->initprot |= 0x2;

	char		*ptr;
	uint32_t	off;
	e->fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (e->fd == -1)
		ft_fatal(NULL, e);
	ptr = (char *)e->file;
	off = lastsec->offset + lastsec->size - woody64_size;

	write(e->fd, ptr, off);
	write(e->fd, &woody64_func, woody64_size);
/* 	write(e->fd, e->key, sizeof(e->key)); */
/* 	write(e->fd, &elf->old_entry, sizeof(elf->old_entry)); */
/* 	write(e->fd, &elf->text_crypted_size, sizeof(elf->text_crypted_size)); */
/* 	write(e->fd, &banner_size, sizeof(banner_size)); */
/* 	if (e->banner && *e->banner) */
/* 	{ */
/* 		write(e->fd, e->banner, banner_size - 1); */
/* 		write(e->fd, "\n", 1); */
/* 	} */
	write(e->fd, ptr + off, e->file_size - off);
	close(e->fd);
	e->fd = 0;
}

void			print_macho64(t_env *e)
{
	struct mach_header_64		*header = (struct mach_header_64 *)e->file;
	uint32_t					offset = sizeof(*header);
	struct load_command			*cmd;
	struct segment_command_64	*segment;
	struct segment_command_64	*segtext;
	struct section_64			*sectext;
	char						maxprot[]  = "(   )";
	char						initprot[] = "(   )";

	ft_printf("addr\t\t magic\t\t bit\t endian\t\t cputype\t cpusubtype\t filetype\t ncmds\t sizecmds\t flags\n");
	ft_printf("%p\t %p\t %s\t %s\t %d\t\t %d\t\t %d\t\t %d\t %d\t\t %#.08x\n",
			  header, header->magic,
			  (!is_64(header->magic)) ? "32" : "64",
			  (!is_swap(header->magic)) ? "little-endian" : "big-endian",
			  header->cputype & ~CPU_ARCH_MASK, header->cpusubtype & ~CPU_SUBTYPE_MASK,
			  header->filetype, header->ncmds,
			  header->sizeofcmds, header->flags);
	ft_printf("\n");

	for (size_t i = 0; i < header->ncmds; i++)
	{
		cmd = (struct load_command *)(e->file + offset);
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if (ft_strcmp(segment->segname, SEG_TEXT) == 0)
				segtext = segment;
			maxprot[1] = (segment->maxprot & 0x1) ? 'R' : ' ';
			maxprot[2] = (segment->maxprot & 0x2) ? 'W' : ' ';
			maxprot[3] = (segment->maxprot & 0x4) ? 'X' : ' ';
			initprot[1] = (segment->initprot & 0x1) ? 'R' : ' ';
			initprot[2] = (segment->initprot & 0x2) ? 'W' : ' ';
			initprot[3] = (segment->initprot & 0x4) ? 'X' : ' ';
			ft_printf("cmd\t\t cmdsize\t segname\t vmaddr\t\t vmsize\t fileoff\t filesize\t maxprot\t initprot\t nsects\t flags\n");
			ft_printf("%-11s\t %#.5x\t %-11s\t %-11p\t %#x\t %#-5x\t\t %#-5x\t\t %d %s\t %d %s\t %-5d\t %#x\n",
					  "LC_SEGMENT_64", segment->cmdsize, segment->segname, segment->vmaddr,
					  segment->vmsize, segment->fileoff, segment->filesize, segment->maxprot, maxprot,
					  segment->initprot, initprot, segment->nsects, segment->flags);
			if (segment->nsects)
			{
				struct section_64 *section = (struct section_64 *)(segment + 1);
				if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
					sectext = section;
				ft_printf("\t section\t segment\t addr\t\t size\t offset\t align\t reloff\t nreloc\t flags\t\t 1\t 2\t3\n");
				for (size_t j = 0; j < segment->nsects; j++)
					ft_printf("\t %-15s %-11s\t %-11p\t %#.5x %#.5x %#x\t %#x\t %#x\t %#.8x\t %#x\t %#x\t %#x\n",
							  section[j].sectname, section[j].segname, section[j].addr,
							  section[j].size, section[j].offset, section[j].align, section[j].reloff,
							  section[j].nreloc, section[j].flags, section[j].reserved1,
							  section[j].reserved2, section[j].reserved3);
			}
		}
		else if (cmd->cmd == LC_MAIN)
		{
			struct entry_point_command *entry = (struct entry_point_command *)cmd;
			ft_printf("cmd\t\t cmdsize\t entryoff\t stacksize\n");
			ft_printf("%-11s\t %#.5x\t %#.5x\t %#x\n",
					  "LC_MAIN", entry->cmdsize, entry->entryoff, entry->stacksize);
		}
		else
			ft_printf("%-11d\t %#.5x\n", cmd->cmd, cmd->cmdsize);
		offset += cmd->cmdsize;
	}
	offset -= sizeof(*header);
}

void			print_hex(u_char *data, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		if (i % 16 == 0)
			ft_printf("\n%p", data);
		if (i % 4 == 0)
			ft_printf(" ");
		ft_printf("%02x", data[i]);
		if (i && ((i + 1) == size || ((i + 1) % 16) == 0))
		{
			size_t j = i + 1;
			size_t len = j % 16;
			if (len)
				len = (16 - len + ((16-len)/4) ) * 2 - 1;
			write(1, "                                     ", len + 1);
			for (uint32_t k = (len) ? j-j%16 : j-16;  k < j; k++)
			{
				ft_printf("%c", ft_isprint(data[k]) ? data[k] : '.');
			}
		}
	}
	ft_printf("\n");
}
