#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/10 04:16:42 by root             ###   ########.fr        #
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
FLAGS	= -Wall -Werror -Wextra
LIBS	= -L $(LIB_DIR) -lft
LIB_DIR	= libft/
INCLUDE	= -I includes -I $(LIB_DIR)/includes
ASM		= nasm
ASMFLAG	= -f elf64

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@
	@make -C $(LIB_DIR)

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)
	$(PRINT_HEX)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(ELF_DIR)/%.s
	$(ASM) $(ASMFLAG) -o $@ $<

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(NAME) objects cleaned...

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)
	@echo $(NAME) erased...

re: fclean all

test: re
	mkdir -p /tmp/test
	cp Ressources/elf64 /tmp/test/elf64
	./$(NAME)
#/tmp/test/elf64 is now infected
	cp /bin/ls /tmp/test/ls
	/tmp/test/elf64
	/tmp/test/ls
#/tmp/test/elf64 and /tmp/test/ls are not re-infected
