/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_printf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:20:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 07:20:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASE_PRINTF_H
# define FT_BASE_PRINTF_H

# include <inttypes.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>

# define PRINTF_BUFF_SIZE	1028
# define ULL				unsigned long long
# define LL					long long
# define PRINTF_ARGS		"sSpdDioOuUxXcC%"
# define PRINTF_FUNC1		pf_s, pf_s, pf_p, pf_di, pf_di, pf_di, pf_o, pf_o
# define PRINTF_FUNC2		pf_u, pf_u, pf_x, pf_x, pf_c, pf_c, pf_percent
# define ARG_H				0x00001
# define ARG_HH				0x00002
# define ARG_L				0x00010
# define ARG_LL				0x00020
# define ARG_J				0x00100
# define ARG_Z				0x00200

typedef struct		s_av
{
	ULL				ui;
	char			*s;
	int				len;
}					t_av;

typedef struct		s_args
{
	char			hash;
	char			minus;
	char			plus;
	char			space;
	char			zero;
	int				min_width;
	char			*point;
	int				precision;
	int				len_modifier;
}					t_args;

typedef struct		s_dt
{
	void			*stream;
	int				fd;
	char			*str;
	size_t			str_size;
	void			(*writeto)(struct s_dt *);
	va_list			ap;
	int				ret;
	unsigned int	less;
	unsigned int	pos;
	char			buff[PRINTF_BUFF_SIZE];
	char			*tail;
	int				len;
	t_args			flag;
}					t_dt;

int					pf_routine(t_dt *data);
void				pf_s(t_dt *data);
void				pf_p(t_dt *data);
void				pf_di(t_dt *data);
void				pf_o(t_dt *data);
void				pf_u(t_dt *data);
void				pf_x(t_dt *data);
void				pf_c(t_dt *data);
void				pf_percent(t_dt *data);
void				write_str(t_dt *data, const char *str, int len);
void				write_char(t_dt *data, unsigned char c);
void				write_wchar(t_dt *data, wchar_t *w, int *len);

char				*ft_strtoupper(char *s);
char				*ft_itoa_base(ULL nb, ULL base);
unsigned char		ft_atouc(char *str);

#endif
