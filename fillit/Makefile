#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/04 22:43:29 by gbourgeo          #+#    #+#              #
#    Updated: 2018/09/04 22:51:10 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	:= fillit

SRC_DIR	= src/
SRC 	= fillit.c solver.c map.c parse.c place.c checking.c

OBJ_DIR	= obj/
OBJ 	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

HDR_DIR	= inc/
LIB_DIR	= libft/
HDRS	:= -I $(HDR_DIR) -I $(LIB_DIR)
LIBS 	:= -L $(LIB_DIR) -lft

FLAGS 	:= -Wall -Werror -Wextra

all : premade $(NAME)

premade:
	@mkdir -p $(OBJ_DIR)
	@make -C $(LIB_DIR)

$(NAME) : $(OBJ)
	gcc -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR_DIR)fillit.h
	gcc $(FLAGS) $(HDRS) -o $@ -c $< 

clean :
	make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean : clean
	make -C $(LIB_DIR) fclean
	/bin/rm -f $(NAME)

re : fclean all

ez :
	rm -rf $(NAME)
	gcc $(INCLUDES) $(LIBS) $(SRC) -o $(NAME)

.PHONY = $(NAME) all clean fclean re
