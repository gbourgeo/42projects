/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 21:36:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/07/04 07:00:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>

# define TYPE		int
# define SIZEOF		(sizeof(TYPE))
# define TINY		1024
# define SMALL		4096

typedef struct		s_head
{
	struct s_head	*next;
	int				length;
}					t_head;

typedef struct		s_zone
{
	size_t			size;
	void			*data;
	struct s_zone	*next;
	struct s_zone	*prev;
}					t_zone;

typedef struct		s_mem
{
	int				initialized;
	pthread_mutex_t	mutex;
	int				page;
	struct rlimit	rlim;
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}					t_mem;

void				*malloc(size_t size);
void				*ft_init_data(t_mem *mem, t_zone **region, size_t size);
t_zone				*ft_init_region(size_t size);
void				*ft_region(t_mem *mem, t_zone **region, size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
void				ft_putstr(char const *str);
void				ft_putnbr(int n);
void				ft_putchar(char c);

#endif
