/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:59:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 14:06:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <sys/types.h>

# ifdef __APPLE__
#  include <mach-o/loader.h>
# elif defined _WIN32 || defined _WIN64

# else
#  include <elf.h>
# endif

typedef struct	s_env
{
	const char	*progname;
	int			fd;
	off_t		file_size;
	void		*file;
	size_t		offset;
	uint64_t	text_vaddr;
	uint32_t	text_crypted_size;
}				t_env;

extern uint64_t	woody_keys[4];
extern uint32_t	woody_size;

int				ft_fatal(char *str, t_env *e);
void			woody_encrypt(u_char *data, size_t len, const uint32_t *key);
void			pack_macho(t_env *e);
void			pack_elf(t_env *e);
void			woody_func(void);


#endif
