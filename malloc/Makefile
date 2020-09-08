# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/14 15:49:42 by gbourgeo          #+#    #+#              #
#    Updated: 2020/07/04 06:49:13 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so

LINK	= libft_malloc.so

SRC		= ft_malloc.c		\
		ft_region.c			\
		ft_free.c			\
		ft_realloc.c		\
		show_alloc_mem.c	\
		ft_putnbr.c			\
		ft_putstr.c			\
		ft_putchar.c

OBJ		= $(SRC:.c=.o)

GWW		= gcc -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -shared -fPIC -o $@ $^
	ln -s $(NAME) $(LINK)

%.o: %.c
	$(GWW) -c $^ -I.

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(LINK)

re: fclean all
