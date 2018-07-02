#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/07/02 23:42:51 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Famine

SRC_DIR	= srcs
SRC		= main.c

ELF_DIR	= $(SRC_DIR)/elf
SRC_S	= famine64.s

OBJ_DIR	=	obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_S	= $(addprefix $(OBJ_DIR), $(SRC_S:.s=.o))

WWW		= gcc
FLAGS	= -Wall -Werror -Wextra -O2
INCLUDE	= -I $(LIB_DIR)/includes
ASM		= nasm
ASMFLAG	= -f elf64

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(ELF_DIR)/%.s
	$(ASM) $(ASMFLAG) -o $@ $<

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(NAME) objects cleaned...

fclean: clean
	@/bin/rm -f $(NAME)
	@echo $(NAME) erased...

re: fclean all
