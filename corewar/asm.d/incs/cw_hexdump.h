/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:54:39 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/24 21:46:35 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_HEXDUMP_H
# define CW_HEXDUMP_H

# include "asm.h"
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <ncurses.h>
# include <curses.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>

# define ERR_SIZE	-1

# define FLAG_N		(1 << 0)
# define FLAG_O		(1 << 1)
# define FLAG_P		(1 << 2)
# define FLAG_GP	(1 << 3)
# define FLAG_D		(1 << 4)
# define FLAG_S		(1 << 5)
# define FLAG_F		(1 << 6)
# define ATLST_ONE	(1 << 8)

# define DASH_N		{FLAG_N, 'n'}
# define DASH_O		{FLAG_O, 'o'}
# define DASH_P		{FLAG_P, 'p'}
# define DASH_GP	{FLAG_GP, 'P'}
# define DASH_D		{FLAG_D, 'd'}
# define DASH_S		{FLAG_S, 's'}
# define DASH_F		{FLAG_F, 'f'}

# define NAME		1
# define COMMENT	2
# define PADDING	4

# define COR_EXT	".cor"
# define MSG_BIS	"With this visu you will be able"
# define MSG_BIS2	" to see a bit more about how corewar works"
# define MSG		MSG_BIS MSG_BIS2
# define ZERO_LINE	"00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00"
# define BOX		"+---------------------------------------------+"
# define BOX_MIDDLE	"|=============================================|"

# define LIVE		{1, "live"}
# define LD			{2, "ld"}
# define ST			{3, "st"}
# define ADD		{4, "add"}
# define SUB		{5, "sub"}
# define AND		{6, "and"}
# define OR			{7, "or"}
# define XOR		{8, "xor"}
# define ZJMP		{9, "zjmp"}
# define LDI		{10, "ldi"}
# define STI		{11, "sti"}
# define FORK		{12, "fork"}
# define LLD		{13, "lld"}
# define LLDI		{14, "lldi"}
# define LFORK		{15, "lfork"}
# define AFF		{16, "aff"}

typedef struct		s_data
{
	int				fd;
	int				pos;
	int				pc;
	int				encoding_byte;
	int				x;
	int				y;
	int				i;
	int				zero;
	int				check;
	WINDOW			*main_win;
	char			*file_name;
	unsigned char	*buffer;
	t_env			*e;
	t_aolist		*ao;
}					t_data;

typedef struct		s_flags
{
	int				msk;
	char			opt;
}					t_flags;

typedef struct		s_opc
{
	int				code;
	char			*opcode;
}					t_opc;

typedef struct		s_thread
{
	WINDOW			*main_win;
	int				stop;
}					t_thread;

void				print_usage(char *error);
char				*basename(char *file);
int					way_to_corewar(t_data *data, t_aolist *ao);

int					create_corfile(t_data *data, char *file);
void				dump(char *file, void *addr, int len);

void				write_name(t_data *data, char *str);
void				write_comment(t_data *data, char *str);
void				write_opc(t_data *data, int opc);
void				write_type(t_data *data, int *tab);
void				write_param(t_data *data, t_token *tok, int *tab);
void				write_header(t_data *data, int type);
void				write_magic(t_data *data);
void				reverse_write(t_data *data, unsigned int param, int count);
short				binary(char dec);

int					init_screen(t_data *data);
int					wait_or_enter(t_data *data, int sleeping);
void				print_hex(t_data *data);
void				print_buff(t_data *data);
int					fill_buffer(t_data *data);
int					len_hex(unsigned char bin);
void				nprint_nb(t_data *data, int base,
		unsigned char n, char letter);
void				print_file_name(t_data *data);
void				print_compilation(t_data *data);
void				print_dot(t_data *data);
void				print_end(t_data *data);
void				print_menu(t_data *data);
void				starting_color(t_data *data);
void				reset_colors(t_data *data);
void				print_legend(t_data *data, int x, int y);
void				print_offset(t_data *data);

void				print_fsize(t_data *data);
void				print_path(t_data *data);
void				print_zero(t_data *data);
void				print_zero_line(t_data *data);
void				check_zero(t_data *data, unsigned char buff);

int					user_file(t_data *data);
int					len_path(char *file);

char				*cut_path(char *file);
void				handle_dotdot(t_data *data);

#endif
