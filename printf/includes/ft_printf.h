/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:17:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 09:57:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <wchar.h>

# define PRINTF_BUFF	1028
# define ULL			unsigned long long
# define LL				long long
# define PRINTF_ARGS	"sSpdDioOuUxXcC%"
# define PRINTF_FUNC1	pf_s, pf_s, pf_p, pf_di, pf_di, pf_di, pf_o, pf_o
# define PRINTF_FUNC2	pf_u, pf_u, pf_x, pf_x, pf_c, pf_c, pf_percent
# define ARG_H			0x00001
# define ARG_HH			0x00002
# define ARG_L			0x00010
# define ARG_LL			0x00020
# define ARG_J			0x00100
# define ARG_Z			0x00200

typedef struct		s_av
{
	ULL				ui;
	char			s[28];
	char			*str;
	size_t			len;
}					t_av;

typedef struct		s_args
{
	char			hash;
	char			minus;
	char			plus;
	char			space;
	char			zero;
	size_t			min_width;
	char			*point;
	size_t			precision;
	int				len_modifier;
}					t_args;

typedef struct		s_dt
{
	va_list			ap;
	char			*tail;
	void			(*write_method)(struct s_dt *);
	void			*stream;
	size_t			stream_size;
	int				ret;
	unsigned int	less;
	unsigned int	pos;
	char			buff[PRINTF_BUFF];
	int				len;
	t_args			flag;
}					t_dt;

int					ft_printf(const char *restrict format, ...);
int					ft_fprintf(FILE *restrict stream, const char *restrict format, ...);
int					ft_sprintf(char *restrict str, const char *restrict format, ...);
int					ft_snprintf(char *restrict str, size_t size, const char *restrict format, ...);
int					ft_asprintf(char **ret, const char *format, ...);
int					ft_dprintf(int fd, const char *restrict format, ...);

void				ft_base(t_dt *data);
char				*ft_strtoupper(char *s);
char				*ft_itoa_base(ULL nb, ULL base);
char				*ft_itoa_base2(ULL nb, ULL base, char *str);
unsigned char		ft_atouc(char *str);
int					ft_wcharlen(wchar_t w);
size_t				ft_wstrlen(const wchar_t *str);
void				pf_s(t_dt *data);
void				pf_p(t_dt *data);
void				pf_di(t_dt *data);
void				pf_o(t_dt *data);
void				pf_u(t_dt *data);
void				pf_x(t_dt *data);
void				pf_c(t_dt *data);
void				pf_percent(t_dt *data);
void				write_str(t_dt *data, const char *str, size_t len);
void				write_char(t_dt *data, unsigned char c);
void				write_wchar(t_dt *data, wchar_t w);
void				write_wstr(t_dt *data, wchar_t *s, size_t len);

#endif
