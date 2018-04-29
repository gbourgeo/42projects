#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2018/04/29 05:07:06 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= woody_woodpacker

SRC_DIR	= srcs/
SRC		= main.c
SRC_A	= woody.s

HDR_DIR	= includes/

OBJ_DIR	= obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_A	= $(addprefix $(OBJ_DIR), $(SRC_A:.s=.o))

LIB_DIR	= libft/
LIB_HDR	= $(LIB_DIR)includes

WWW 	= gcc
FLAGS	= -Wall -Werror -Wextra
INCLUDE	= -I$(HDR_DIR) -I$(LIB_HDR)
LIBS	= -L$(LIB_DIR) -lft

ASM		= nasm
AFLAGS	= -f elf64

all: lib $(NAME)

$(NAME): $(OBJ) $(OBJ_A)
	$(WWW) -o $@ $^ $(LIBS)
	$(WWW) $(FLAGS) -o $(OBJ_DIR)file_info.o -c $(SRC_DIR)file_info.c $(INCLUDE)
	$(WWW) -o hex $(OBJ_DIR)file_info.o $(LIBS) # !!!!

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	$(ASM) $(AFLAGS) -o $@ $<

.PHONY: lib clean fclean re

lib:
	@make -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
#	@make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
#	@make -C $(LIB_DIR) fclean
	/bin/rm -f woody
	/bin/rm -f $(NAME)
	/bin/rm -f hex

re: fclean all
