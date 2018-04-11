#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2018/04/10 22:01:05 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Durex
SRC		= main.c
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRC_DIR	= srcs/
HDR_DIR = includes/
OBJ_DIR	= objs/

FLAGS	= -Wall -Werror -Wextra

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(HDR_DIR)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
