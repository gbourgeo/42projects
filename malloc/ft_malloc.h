/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 21:36:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/10 18:51:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/resource.h>

# define TYPE		int
# define SIZEOF		(sizeof(TYPE))
# define TINY		1024
# define SMALL		4096

typedef struct		s_zone
{
	size_t			size;
	void			*data;
	struct s_zone	*next;
	struct s_zone	*prev;
}					t_zone;

typedef struct		s_mem
{
	struct rlimit	rlim;
	int				page;
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}					t_mem;

struct s_mem		mem_list;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
void				ft_putstr(char const *str);
void				ft_putnbr(int n);
void				ft_putchar(char c);

#endif
