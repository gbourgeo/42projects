#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/13 14:38:29 by gbourgeo          #+#    #+#              #
#    Updated: 2017/07/13 14:41:40 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_display_file

SRC = ft_display_file.c

OBJ = $(SRC:.c=.o)

WWW = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^

%.o: %.c
	$(WWW) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
