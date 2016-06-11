#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2016/06/11 12:24:47 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = woody_woodpacker

SRC = main.c

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT = libft

LIBFT_H = $(LIBFT)/includes

WWW = gcc -Wall -Werror -Wextra

all: lib $(NAME)

lib:
	@make -C $(LIBFT)
	@mkdir -p $(OBJ_DIR)

.PHONY: all lib clean fclean re

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ -L $(LIBFT) -lft -I $(LIBFT_H)

$(OBJ_DIR)%.o: %.c woody.h
	$(WWW) -o $@ -c $< -I $(LIBFT_H)

clean:
#	@make -C $(LIBFT) clean
	@if test -d $(OBJ_DIR) ; then /bin/rm -rf $(OBJ_DIR) ; echo rm -f $(OBJ) ; fi

fclean: clean
#	@make -C $(LIBFT) fclean
	@if test -f $(NAME) ; then /bin/rm -f $(NAME) ; echo rm -f $(NAME) ; fi

re: fclean all