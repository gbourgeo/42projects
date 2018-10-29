#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 06:23:06 by gbourgeo          #+#    #+#              #
#    Updated: 2018/10/29 06:40:13 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= minitalk

SRC_D	= src/
SRC		= minitalk.c socket.c loop.c clear.c

OBJ_D	= obj/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

INC		= inc/

FLAGS	= -Wall -Werror -Wextra

LIBS	= 

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ)
	gcc -o $@ $^ $(LIBS)

$(OBJ_D)%.o: $(SRC_D)%.c $(INC)minitalk.h
	gcc $(FLAGS) -o $@ -c $< -I$(INC)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
