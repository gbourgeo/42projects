# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 10:47:53 by mmonier           #+#    #+#              #
#    Updated: 2019/09/18 18:40:05 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

NAME = libft.a

HEADER = inc/

OBJ_D = objs/

SRCS = 	ft_memset.c										\
	   	ft_bzero.c										\
	   	ft_memcpy.c										\
	   	ft_memccpy.c									\
	   	ft_memmove.c									\
	   	ft_memchr.c										\
	   	ft_memcmp.c 									\
	   	ft_strlen.c										\
	   	ft_strdup.c										\
	   	ft_strcpy.c										\
	   	ft_strncpy.c									\
	   	ft_strcat.c 									\
	   	ft_strncat.c 									\
	   	ft_strlcat.c 									\
	   	ft_strchr.c 									\
	   	ft_strrchr.c 									\
	   	ft_strstr.c 									\
	   	ft_strnstr.c 									\
	   	ft_strcmp.c 									\
		ft_strncmp.c 									\
	   	ft_atoi.c										\
		ft_isalpha.c 									\
		ft_isdigit.c 									\
		ft_isalnum.c 									\
		ft_isascii.c 									\
		ft_isprint.c 									\
		ft_toupper.c 									\
		ft_tolower.c 									\
		ft_memalloc.c 									\
		ft_memdel.c 									\
		ft_strnew.c 									\
		ft_strdel.c 									\
		ft_strclr.c 									\
		ft_striter.c 									\
		ft_striteri.c 									\
		ft_strmap.c 									\
		ft_strmapi.c 									\
		ft_strequ.c 									\
		ft_strnequ.c 									\
		ft_strsub.c 									\
		ft_strjoin.c 									\
		ft_strtrim.c 									\
		ft_strsplit.c 									\
		ft_itoa.c 										\
		ft_putchar.c 									\
		ft_putstr.c 									\
		ft_putendl.c 									\
		ft_putnbr.c 									\
		ft_putchar_fd.c 								\
		ft_putstr_fd.c 									\
		ft_putendl_fd.c 								\
		ft_putnbr_fd.c 									\
		ft_lstnew.c 									\
		ft_lstdelone.c 									\
		ft_lstdel.c 									\
		ft_lstadd.c 									\
		ft_lstiter.c 									\
		ft_lstmap.c 									\
		ft_reverse.c 									\
		ft_swap.c 										\
		ft_puttab.c 									\
		ft_isspace.c 									\
		ft_count_occ.c 									\
		ft_strnword.c 									\
		ft_putsnbr.c 									\
		ft_sort_all.c 									\
		ft_swap_all.c 									\
		ft_intcmp_void.c 								\
		ft_strcmp_void.c 								\
		ft_strjoinfree.c 								\
		ft_strjoin_c.c 									\
		ft_touppercase.c 								\
		ft_strrev.c										\
		ft_printf.c										\
		ft_dprintf.c									\
		ft_parse.c										\
		get_next_line.c									\
		ft_strfjoin.c									\
		ft_rand.c										\
		ft_atoi_base.c									\

OBJS = $(addprefix $(OBJ_D), $(SRCS:.c=.o))

CONV_D = converter/
CONV_S = get_converter.c					\
		convert_c.c							\
		convert_s.c							\
		convert_o.c							\
		convert_p.c							\
		convert_x.c							\
		convert_gx.c						\
		convert_u.c							\
		convert_f.c							\
		convert_d.c							\
		convert_b.c							\
		convert_r.c							\
		convert_gc.c						\
		convert_gs.c						\
		convert_gr.c						\
		convert_k.c							\
		convert_color.c						\
		convert_star.c						\

OBJS += $(addprefix $(OBJ_D), $(CONV_S:.c=.o))

TOOL_D = tools/
TOOL_S = float_to_string.c						\
		ft_utoa.c								\
		len_func.c								\
		get_date.c								\
		get_flags.c								\
		write_wchar.c							\
		get_valist.c							\
		get_args.c								\
		get_arg_int.c							\
		convert_base.c							\
		write_char.c							\
		get_char_conv.c							\
		apostrophe_flag.c						\
		convert_ubase.c							\
		ft_intmax_toa.c							\
		check_mask.c							\
		get_specifier.c							\

OBJS += $(addprefix $(OBJ_D), $(TOOL_S:.c=.o))

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(OBJ_D)%.o:%.c
	$(CC) -o $@ $(CFLAGS) -I $(HEADER) -c $<

$(OBJ_D)%.o:$(CONV_D)%.c
	$(CC) -o $@ $(CFLAGS) -I $(HEADER) -c $<

$(OBJ_D)%.o:$(TOOL_D)%.c
	$(CC) -o $@ $(CFLAGS) -I $(HEADER) -c $<

$(NAME): $(OBJS)
	ar rc $@ $^
	ranlib $@

clean:
	$(RM) $(OBJ_D)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

