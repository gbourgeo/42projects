#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/07 21:22:32 by gbourgeo          #+#    #+#              #
#    Updated: 2014/02/10 16:58:15 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= server

NAME2	= client

SRC		= server.c ft_realloc.c

SRC2	= client.c

OBJ		= $(SRC:.c=.o)

OBJ2	= $(SRC2:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= libft/includes/

.PHONY: clean fclean re all

all: $(NAME) $(NAME2)

$(NAME): server.h
	make -C $(LIBFT)
	gcc $(FLAGS) -c $(SRC) -I $(LIBFT_H)
	gcc -o $(NAME) $(OBJ) -L $(LIBFT) -lft -O3

$(NAME2):
	gcc $(FLAGS) -c $(SRC2) -I $(LIBFT_H)
	gcc -o $(NAME2) $(OBJ2) -L $(LIBFT) -lft -O3

clean:
	@make -C $(LIBFT) clean
	rm -f $(OBJ)
	rm -f $(OBJ2)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)
	rm -f $(NAME2)

re: fclean all
