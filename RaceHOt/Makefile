#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/15 05:31:47 by gbourgeo          #+#    #+#              #
#    Updated: 2013/12/15 21:03:20 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = hotrace

SRC = hotrace.c ft_add_node.c ft_search_node.c ft_memalloc.c ft_putstr.c \
	ft_strjoin.c ft_strcmp.c get_next_line.c

OBJ = $(SRC:.c=.o)

WWW = -Wall -Werror -Wextra -O3

all: $(NAME)

$(NAME):
	gcc $(WWW) -c $(SRC)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
