/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elf_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:09:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/06/30 23:39:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

static void		check_header_offsets_64(t_env *e)
{
	Elf64_Ehdr *hdr;

	hdr = e->file;
	if (hdr->e_phoff != sizeof(Elf64_Ehdr)
	|| hdr->e_phoff + hdr->e_phnum * sizeof(Elf64_Phdr) > (Elf64_Off)e->file_size)
		ft_fatal("Invalid ELF Program header offset.", e);
	if (hdr->e_shoff < sizeof(Elf64_Ehdr)
	|| hdr->e_shoff + hdr->e_shnum * sizeof(Elf64_Shdr) > (Elf64_Off)e->file_size)
		ft_fatal("Invalid ELF Section header offset.", e);
	if (hdr->e_ehsize != sizeof(Elf64_Ehdr))
		ft_fatal("Invalid ELF Header size.", e);
	if (hdr->e_phentsize != sizeof(Elf64_Phdr))
		ft_fatal("Invalid ELF Program header size.", e);
	if (hdr->e_shentsize != sizeof(Elf64_Shdr))
		ft_fatal("Invalid ELF Section header size.", e);
	if (hdr->e_shstrndx >= hdr->e_shnum)
		ft_fatal("Invalid ELF Section string index offset.", e);
}

static void		check_header_offsets_32(t_env *e)
{
	Elf32_Ehdr *hdr;

	hdr = e->file;
	if (hdr->e_phoff != sizeof(Elf32_Ehdr)
	|| hdr->e_phoff + hdr->e_phnum * sizeof(Elf32_Phdr) > (Elf32_Off)e->file_size)
		ft_fatal("Invalid ELF Program header offset.", e);
	if (hdr->e_shoff < sizeof(Elf32_Ehdr)
	|| hdr->e_shoff + hdr->e_shnum * sizeof(Elf32_Shdr) > (Elf32_Off)e->file_size)
		ft_fatal("Invalid ELF Section header offset.", e);
	if (hdr->e_ehsize != sizeof(Elf32_Ehdr))
		ft_fatal("Invalid ELF Header size.", e);
	if (hdr->e_phentsize != sizeof(Elf32_Phdr))
		ft_fatal("Invalid ELF Program header size.", e);
	if (hdr->e_shentsize != sizeof(Elf32_Shdr))
		ft_fatal("Invalid ELF Section header size.", e);
	if (hdr->e_shstrndx >= hdr->e_shnum)
		ft_fatal("Invalid ELF Section string index offset.", e);
}

static void		check_header(t_env *e)
{
	Elf64_Ehdr *hdr;

	hdr = e->file;
	if (ft_memcmp(hdr->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF magic.", e);
	if (hdr->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF version.", e);
	if (ft_strcmp(&e->progname[ft_strlen(e->progname) - 2], "32") == 0)
	{
		if (hdr->e_ident[EI_CLASS] != ELFCLASS32)
			ft_fatal("Unsupported ELF Class (32 bit only).", e);
	}
	else if (hdr->e_ident[EI_CLASS] != ELFCLASS64)
		ft_fatal("Unsupported ELF Class (64 bit only).", e);
	if (hdr->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF Byte order.", e);
	if (hdr->e_type != ET_EXEC && hdr->e_type != ET_DYN)
		ft_fatal("Unsupported ELF Type.", e);
	if (hdr->e_machine != EM_X86_64 && hdr->e_machine != EM_386) /* AMD x86_64 */
		ft_fatal("Unsupported ELF Architecture.", e);
	if (hdr->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF Version.", e);
	if (hdr->e_machine == EM_X86_64)
		check_header_offsets_64(e);
	else
		check_header_offsets_32(e);
}

void			check_elf_info(t_env *e)
{
	if ((size_t)e->file_size < sizeof(Elf64_Ehdr))
		ft_fatal("Invalid ELF size.", e);
	check_header(e);
}
