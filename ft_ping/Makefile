#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/03 22:45:44 by gbourgeo          #+#    #+#              #
#    Updated: 2017/03/28 22:13:16 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ping

SRC_DIR = src/

SRC = ft_analyse.c ft_init.c ft_ping.c ft_pinger.c ft_setup.c ft_signals.c ft_atod.c

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT = libft

LIB_H = $(LIBFT)/includes

WWW = gcc -Wall -Werror -Wextra

all: lib $(OBJ_DIR) $(NAME)

lib:
	make -C $(LIBFT)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ) | $(LIBFT)/libft.a
	$(WWW) -o $@ $^ -L $(LIBFT) -lft
	@echo "CREATED:" $(NAME);

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(SRC_DIR)ft_ping.h | $(OBJ_DIR)
	$(WWW) -o $@ -c $< -I $(LIB_H)

clean:
	@make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
