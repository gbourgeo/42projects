#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/25 09:36:09 by gbourgeo          #+#    #+#              #
#    Updated: 2018/09/25 09:42:11 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=test

SRC=main.c

OBJ=$(SRC:.c=.o)

FLAGS=-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^

%.o:%.c
	gcc $(FLAGS) -c $<

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
