#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/29 20:03:31 by gbourgeo          #+#    #+#              #
#    Updated: 2016/05/19 20:23:15 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

SRC = main.c ft_fractol.c hooks.c hooks_two.c ft_put_color.c ft_end.c \
	ft_draw_mandel.c ft_draw_julia.c ft_draw_ship.c ft_draw_brain.c \
	ft_change_color.c

OBJ = $(SRC:.c=.o)

LIBFT = libft

HDR = $(LIBFT)/includes

LIBX = /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIBX_H = -I /usr/local/include

CC = gcc

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBFT) -lft -L $(LIBX)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $^ -I $(HDR) $(LIBX_H)

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIBFT)/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
