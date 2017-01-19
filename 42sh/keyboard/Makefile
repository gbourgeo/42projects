#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/14 16:43:50 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/14 16:57:12 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libkeys

SRC		= ft_key_control.c	\
		ft_key_search.c		\
		ft_key_suppr.c		\
		ft_normal_keys.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

HEADR	= -I..

.PHONY: clean fclean re all message

all: message $(NAME)

$(NAME): $(OBJ)
	@echo " OK"

%.o: %.c
	@echo -n .
	@gcc $(FLAGS) -c $(SRC) $(HEADR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

message:
	@echo -n - Compilation du Keyboard