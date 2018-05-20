#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/05/20 20:25:52 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Famine

SRC_DIR	= srcs/
SRC		= main.c

OBJ_DIR	=	obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_DIR	= libft/
INCLUDE	= -I includes -I $(LIB_DIR)/includes

WWW		= gcc
FLAGS	= -Wall -Werror -Wextra
LIBS	= -L $(LIB_DIR) -lft

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@
	@make -C $(LIB_DIR)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(NAME) objects cleaned...

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)
	@echo $(NAME) erased...

re: fclean all
