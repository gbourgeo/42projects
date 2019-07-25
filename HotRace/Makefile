#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/15 05:31:47 by gbourgeo          #+#    #+#              #
#    Updated: 2013/12/15 21:27:20 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = hotrace

SRC = ft_create_node.c ft_memalloc.c ft_putstr.c ft_search_node.c ft_strcmp.c \
	ft_strjoin.c get_next_line.c hotrace.c ft_hash.c ft_add_node.c \
	ft_shake_tree.c

OBJ = $(SRC:.c=.o)

WWW = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(WWW) -c $(SRC)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
