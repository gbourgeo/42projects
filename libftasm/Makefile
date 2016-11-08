#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/01 23:37:59 by root              #+#    #+#              #
#    Updated: 2016/11/08 21:19:42 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libfts.a

SRC_DIR = src/

SRC = ft_bzero.s ft_strcat.s ft_isalpha.s ft_isdigit.s ft_isalnum.s \
		ft_isascii.s ft_isprint.s ft_toupper.s ft_tolower.s ft_puts.s \
		ft_strlen.s ft_memset.s ft_memcpy.s ft_strdup.s ft_cat.s \
		ft_memchr.s ft_memrchr.s ft_memcmp.s ft_putnbr.s ft_iter.s

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.s=.o))

HDR = includes/

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	/Users/gbourgeo/homebrew/Cellar/nasm/2.12.02/bin/nasm -f macho64 $< -o $@
#	nasm -f elf64 $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f test

re: fclean all

test: re
	gcc -Wall -Werror -Wextra -o test test.c $(NAME) -I $(HDR)
