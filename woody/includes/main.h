/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:59:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/16 09:32:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/types.h>
# ifdef __linux__
#  include <elf.h>
# elif __APPLE__
#  include <mach-o/loader.h>
# endif

typedef struct	s_env
{
	const char	*progname;
	char		*banner;
	uint32_t	banner_len;
	int			fd;
	off_t		file_size;
	void		*file;
	uint32_t	key[4];
	size_t		woody_datalen;
}				t_env;

# ifdef __linux__
typedef struct	s_elf32
{
	Elf32_Ehdr	*header;
	Elf32_Phdr	*program;
	Elf32_Phdr	*text_program;
	Elf32_Phdr	*woody_program;
	Elf32_Shdr	*section;
	Elf32_Shdr	*text_section;
	Elf32_Addr	old_entry;
	Elf32_Addr	vaddr;
	uint32_t	text_crypted_size;
	u_char		padding[8];
}				t_elf32;

typedef struct	s_elf64
{
	Elf64_Ehdr	*header;
	Elf64_Phdr	*program;
	Elf64_Phdr	*text_program;
	Elf64_Phdr	*woody_program;
	Elf64_Shdr	*section;
	Elf64_Shdr	*text_section;
	Elf64_Addr	old_entry;
	Elf64_Addr	vaddr;
	uint64_t	text_crypted_size;
}				t_elf64;
# elif __APPLE__
typedef struct					s_macho64
{
	struct mach_header_64		*header;
	struct entry_point_command	*entry;
	struct segment_command_64	*segtext;
	struct section_64			*sectext;
	struct segment_command_64	*lastseg;
	struct section_64			*lastsect;
	struct segment_command_64	newseg;
	struct section_64			newsect;
	uint64_t					old_entryoff;
	uint64_t					new_entryoff;
	uint32_t					text_crypted_size;
}								t_macho64;
# endif

int				ft_fatal(char *str, t_env *e);
void			generate_new_key(uint32_t key[4]);
void			get_elf_info(t_env *e);
void			pack_elf32(t_env *e);
void			pack_elf64(t_env *e);
void			get_macho_info(t_env *e);
void			pack_macho32(t_env *e);
void			pack_macho64(t_env *e);
uint32_t		ft_swap_bytes(uint32_t num);

#endif
