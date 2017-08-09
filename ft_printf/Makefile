#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/05 01:54:08 by gbourgeo          #+#    #+#              #
#    Updated: 2017/08/09 21:25:39 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SRC_DIR = src/

SRC = ft_printf.c		\
		ft_itoa.c		\
		ft_memset.c		\
		ft_putnbr.c		\
		ft_strncat.c	\
		ft_strnew.c		\
		ft_strlen.c		\
		ft_strtoupper.c

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

HEADER = -I includes/

WWW = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo CREATED: $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(WWW) -o $@ -c $< $(HEADER)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

test: re
	gcc main.c -Iincludes -L. -lftprintf && ./a.out