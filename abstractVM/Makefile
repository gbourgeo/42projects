# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/26 21:29:25 by gbourgeo          #+#    #+#              #
#    Updated: 2019/07/26 21:40:27 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= avm

SRC_D	= srcs/
SRC_F	= main.cpp

INC_D	= includes/

OBJ_D	= objs/
OBJ_F	= $(addprefix $(OBJ_D), $(SRC_F:.cpp=.o))

CC		= g++
FLAGS	= -Wall -Werror -Wextra

all: objs $(NAME)

objs:
	mkdir -p $@

$(NAME): $(OBJ_F)
	$(CC) -o $@ $<

$(OBJ_D)%.o: $(SRC_D)%.cpp
	$(CC) $(FLAGS) -o $@ -c $^ -I $(INC_D)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
