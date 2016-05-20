#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/18 13:43:18 by gbourgeo          #+#    #+#              #
#    Updated: 2016/05/13 16:56:51 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= fdf

SRC		= main.c \
	get_map.c \
	get_next_line.c\
	ft_free.c \
	get_coord.c \
	ft_strangesplit.c \
	fdf.c \
	ft_draw.c \
	ft_draw_parallel.c \
	ft_draw_isometric.c \
	ft_draw_conic.c \
	ft_put_color.c \
	key_hook_func.c \
	ft_clear_image.c \
	ft_draw_cases.c \
	ft_abs.c \
	ft_pow.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBX	= -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIBX_H	= /usr/X11/include/

LIBFT	= libft/

LIBFT_H	= libft/includes

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -o $(NAME) $(OBJ) $(LIBX) -L $(LIBFT) -lft

%.o: %.c
	gcc $(FLAGS) -o $@ -c $^ -I $(LIBX_H) -I $(LIBFT_H)

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
