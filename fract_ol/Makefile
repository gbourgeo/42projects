#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/29 20:03:31 by gbourgeo          #+#    #+#              #
#    Updated: 2018/09/16 23:07:20 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

SRC_D = srcs/
SRC = main.c ft_fractol.c hooks.c hooks_two.c ft_put_color.c ft_end.c \
	ft_draw_mandel.c ft_draw_julia.c ft_draw_ship.c ft_draw_brain.c \
	ft_change_color.c

OBJ_D = obj/
OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

LIBFT = libft

HDRS = -I includes/ -I $(LIBFT)/includes -I /usr/local/include

LIBX = -L $(LIBFT) -lft -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

CC = gcc

FLAGS = -Wall -Werror -Wextra

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(FLAGS) -o $@ $^ $(LIBX)

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(FLAGS) -o $@ -c $< $(HDRS)

clean:
	make -C $(LIBFT) clean
	rm -r $(OBJ_D)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
