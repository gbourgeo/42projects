/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elf_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:09:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/11 22:10:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			get_elf_info(t_env *e)
{
	void		(*pack_elf[2])(t_env *) = { pack_elf32, pack_elf64 };
	Elf64_Ehdr	*file_header;
	
	file_header = (Elf64_Ehdr *)e->file;
	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type.", e);
	if (file_header->e_ident[EI_CLASS] == ELFCLASSNONE)
		ft_fatal("Unsupported ELF file class.", e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order.", e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", e);
	if (file_header->e_type != ET_EXEC)
		ft_fatal("Unsupported ELF file type.", e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version.", e);
	generate_new_key(e->key);
	pack_elf[file_header->e_ident[EI_CLASS] - 1](e);
}
