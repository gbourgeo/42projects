#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/07 18:01:32 by ppellegr          #+#    #+#              #
#    Updated: 2014/05/11 22:28:32 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= philo

SRC			= main.c ft_start_routine.c mlx.c main_mlx.c

OBJ			= $(SRC:.c=.o)

CC			= gcc

CFLAGS		= -Werror -Wall -Wextra

LIB_LIBFT	= -L libft -lft

LIB_MLX		= -L /usr/X11/lib -lmlx -lXext -lX11

INCLUDES	= -I libft/includes

all: $(NAME)

$(NAME):
	make -C libft/
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_LIBFT) $(LIB_MLX)

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
