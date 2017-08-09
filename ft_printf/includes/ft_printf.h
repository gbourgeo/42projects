/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:17:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/09 21:21:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdlib.h>

enum				e_args
{
	ARG_X,
	ARG_S,
	ARG_D,
	ARG_C
};

typedef struct		s_args
{
	int				pad_left;
	int				pad_right;
	char			type;
	unsigned int	ui;
	char			*s;
	int				len;
	struct s_args	*next;
}					t_args;

typedef struct		s_dt
{
    int				ret;
	char			*buff;
    char			*head;
    char			*tail;
	int				len;
	t_args			*args;
	t_args			*last;
}					t_dt;

/* typedef struct		s_buf */
/* { */
/* 	char			buf[BUF_SIZE]; */
/* 	struct s_buf	*next; */
/* }					t_buf; */

int					ft_printf(const char * restrict format, ...);
char				*ft_itoa(int i);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strtoupper(char *s);
size_t				ft_strlen(const char *s);


#endif
