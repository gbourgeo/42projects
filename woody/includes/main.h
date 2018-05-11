/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:59:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/11 12:19:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <elf.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/types.h>

typedef struct	s_env
{
	const char	*progname;
	char		*banner;
	int			fd;
	off_t		file_size;
	void		*file;
	Elf64_Addr	old_entry;
	Elf64_Phdr	*woody_program;
	Elf64_Phdr	*text_program;
	uint64_t	text_crypted_size;
	uint32_t	key[4];
	size_t		woody_datalen;
}				t_env;

int				ft_fatal(char *str, t_env *e);
void			generate_new_key(uint32_t key[4]);

#endif
