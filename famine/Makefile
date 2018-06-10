#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/10 05:32:22 by root             ###   ########.fr        #
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
	@rm -rf /tmp/test /tmp/test2
	@mkdir -p /tmp/test /tmp/test2
	@gcc -o Ressources/elf64 -m64 Ressources/sample.c
	@echo -n "TEST 1: The Infection ..."
	@cp Ressources/elf64 /tmp/test/elf64
	@cp Ressources/elf64 /tmp/test2/elf64
	@./$(NAME)
ifeq ($(shell strings /tmp/test/elf64 | grep Famine | wc -l)$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)$(shell /tmp/test/elf64)$(shell /tmp/test2/elf64), 11$(shell Ressources/elf64)$(shell Ressources/elf64))
	@echo " Passed !"
else
	@echo " Failed !"
endif

	@echo -n "TEST 2: No Re-Infection ..."
	@./$(NAME)
ifeq ($(shell strings /tmp/test/elf64 | grep Famine | wc -l)$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)$(shell /tmp/test/elf64)$(shell /tmp/test2/elf64), 11$(shell Ressources/elf64)$(shell Ressources/elf64))
	@echo " Passed !"
else
	@echo " Failed !"
endif

	@echo -n "TEST 3: The In-fect-ception..."
	@cp /bin/ls /tmp/test/ls
	@cp /bin/ls /tmp/test2/ls
ifeq ($(shell /tmp/test/elf64)$(shell strings /tmp/test/* | grep Famine | wc -l)$(shell strings /tmp/test2/* | grep Famine | wc -l)$(shell /tmp/test/ls)$(shell /tmp/test/ls srcs), $(shell Ressources/elf64)22$(shell /bin/ls)$(shell /bin/ls srcs))
	@echo " Passed !"
else
	@echo " Failed !"
endif

