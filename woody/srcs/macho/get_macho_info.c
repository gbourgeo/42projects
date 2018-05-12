/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:27:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/12 19:30:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "main.h"

void			pack_macho32(t_env *e)
{
	(void)e;
}

void			pack_macho64(t_env *e)
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
		if (cmd->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *segment = (struct segment_command_64 *)cmd;
			maxprot[1] = (segment->maxprot & 0x1) ? 'R' : ' ';
			maxprot[2] = (segment->maxprot & 0x2) ? 'W' : ' ';
			maxprot[3] = (segment->maxprot & 0x4) ? 'X' : ' ';
			initprot[1] = (segment->initprot & 0x1) ? 'R' : ' ';
			initprot[2] = (segment->initprot & 0x2) ? 'W' : ' ';
			initprot[3] = (segment->initprot & 0x4) ? 'X' : ' ';
			ft_printf("%-11d\t %#.5x\t %-11s\t %-11p\t %#x\t %#-5x\t\t %#-5x\t\t %d %s\t %d %s\t %-5d\t %#x\n",
					  segment->cmd, segment->cmdsize, segment->segname, segment->vmaddr,
					  segment->vmsize, segment->fileoff, segment->filesize, segment->maxprot, maxprot,
					  segment->initprot, initprot, segment->nsects, segment->flags);
		}
		else if (cmd->cmd == LC_SEGMENT)
		{
			struct segment_command *segment = (struct segment_command *)cmd;
			ft_printf("%-11d\t %#.5x\t %-11s\t %-11p\t %#x\t %#-5x\t\t %#-5x\t\t %-11d\t %-11d\t %-5d\t %#x\n",
					  segment->cmd, segment->cmdsize, segment->segname, segment->vmaddr,
					  segment->vmsize, segment->fileoff, segment->filesize, segment->maxprot,
					  segment->initprot, segment->nsects, segment->flags);
		}
		else
		{
			ft_printf("%-11d\t %d\n", cmd->cmd, cmd->cmdsize);
		}
		offset += cmd->cmdsize;
	}
}

void			get_macho_info(t_env *e)
{
	struct mach_header	*header;
	uint32_t			magic;

	header = (struct mach_header *)e->file;
	magic = header->magic;
	if (magic != MH_MAGIC && magic != MH_CIGAM &&
		magic != MH_MAGIC_64 && magic != MH_CIGAM_64)
		ft_fatal("Invalid MACHO file type", e);
	if (header->filetype != MH_EXECUTE)
		ft_fatal("Unsupported MACHO file type", e);

	ft_printf("addr\t\t magic\t\t bit\t endian\t\t cputype\t cpusubtype\t filetype\t ncmds\t sizecmds\t flags\n");
	ft_printf("%p\t %p\t %s\t %s\t %d\t\t %d\t\t %d\t\t %d\t %d\t\t %#.08x\n", header, header->magic,
			  (magic == MH_MAGIC || magic == MH_CIGAM) ? "32" : "64",
			  (magic == MH_MAGIC || magic == MH_MAGIC_64) ? "big-endian" : "little-endian",
			  header->cputype & ~CPU_ARCH_MASK, header->cpusubtype & ~CPU_SUBTYPE_MASK,
			  header->filetype, header->ncmds,
			  header->sizeofcmds, header->flags);

	if (magic == MH_MAGIC || magic == MH_CIGAM)
		pack_macho32(e);
	else
		pack_macho64(e);
}
