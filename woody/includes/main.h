/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 04:59:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 01:07:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include "elf.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
//# include <mach-o/swap.h>
/* # include <string.h> */
/* # include <errno.h> */

typedef struct	s_env
{
	const char	*progname;
	int			fd;
	off_t		file_size;
	void		*file;
}				t_env;


#endif
