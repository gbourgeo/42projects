/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:59:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/05 12:51:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <elf.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct	s_env
{
	const char	*progname;
	int			fd;
	off_t		file_size;
	void		*file;
	Elf64_Addr	old_entry;
	Elf64_Phdr	*woody_program;
	Elf64_Phdr	*text_program;
	uint32_t	text_vaddr;
	uint32_t	text_crypted_size;
}				t_env;

#endif
