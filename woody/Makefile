#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2018/04/11 05:02:42 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= woody_woodpacker

SRC_DIR	= srcs/
SRC		= main.c

HDR_DIR	= includes/

OBJ_DIR	= obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_DIR	= libft/
LIB_HDR	= $(LIB_DIR)includes

WWW 	= gcc
FLAGS	= -Wall -Werror -Wextra

all: lib $(NAME)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ -L$(LIB_DIR) -lft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< -I$(HDR_DIR) -I$(LIB_HDR)

.PHONY: lib clean fclean re

lib:
	@make -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	/bin/rm -f $(NAME)

re: fclean all
