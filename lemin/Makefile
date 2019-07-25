#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/13 19:08:22 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/19 18:54:54 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

SRC = main.c		\
	ft_init.c		\
	ft_add_room.c	\
	ft_add_links.c	\
	ft_find_room.c	\
	ft_check_paths.c\
	ft_str2join.c	\
	ft_get_paths.c	\
	ft_print_lemmins.c\
	ft_sort_paths.c

OBJ = $(SRC:.c=.o)

WWW = -Wall -Werror -Wextra

LIBFT = libft

LIBFT_H = libft/includes

.PHONY: all clean fclean re

all: comp $(NAME)

comp:
	make -C $(LIBFT)

$(NAME): $(OBJ)
		gcc -o $(NAME) $(OBJ) -L $(LIBFT) -lft

%.o: %.c
	gcc $(WWW) -c $^ -I $(LIBFT_H)

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
