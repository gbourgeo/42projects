#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/10 09:51:27 by root             ###   ########.fr        #
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
#	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(NAME) objects cleaned...

fclean: clean
#	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)
	@echo $(NAME) erased...

re: fclean all

test: re
	@rm -rf /tmp/test /tmp/test2
	@mkdir -p /tmp/test /tmp/test2
	@gcc -o /tmp/test/elf64 -m64 Ressources/sample.c
	@gcc -o /tmp/test2/elf64 -m64 Ressources/sample.c
	@echo -n "TEST 1: The Infection ..."
	@./$(NAME)
ifeq ($(shell strings /tmp/test/elf64 | grep Famine | wc -l)$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)$(shell /tmp/test/elf64)$(shell /tmp/test2/elf64), 11$(shell Ressources/elf64)$(shell Ressources/elf64))
	@echo " Passed !"
else
	@echo " Failed !"
	@echo "Got      : "$(shell strings /tmp/test/elf64 | grep Famine | wc -l)$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)$(shell /tmp/test/elf64)$(shell /tmp/test2/elf64)
	@echo "Expected : "11$(shell Ressources/elf64)$(shell Ressources/elf64)
	@exit 1
endif

	@echo -n "TEST 2: No Re-Infection ..."
	@./$(NAME)
ifeq ($(shell strings /tmp/test/elf64 | grep Famine | wc -l)$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)$(shell /tmp/test/elf64)$(shell /tmp/test2/elf64), 11$(shell Ressources/elf64)$(shell Ressources/elf64))
	@echo " Passed !"
else
	@echo " Failed !"
	@echo "Got      : "$(shell strings /tmp/test/elf64 | grep Famine | wc -l)$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)$(shell /tmp/test/elf64)$(shell /tmp/test2/elf64)
	@echo "Expected : "11$(shell Ressources/elf64)$(shell Ressources/elf64)
	@exit 1
endif

	@echo -n "TEST 3: The In-fect-ception ..."
	@cp /bin/ls /tmp/test/ls
	@cp /bin/ls /tmp/test2/ls
	@/tmp/test/elf64 1>/dev/null
ifeq ($(shell strings /tmp/test/* | grep Famine | wc -l)$(shell strings /tmp/test2/* | grep Famine | wc -l)$(shell /tmp/test/ls)$(shell /tmp/test2/ls srcs), 22$(shell /bin/ls)$(shell /bin/ls srcs))
	@echo " Passed !"
else
	@echo " Failed !"
	@echo "Got      : "$(strings /tmp/test/* | grep Famine | wc -l)$(shell strings /tmp/test2/* | grep Famine | wc -l)$(shell /tmp/test/ls /tmp/test)$(shell /tmp/test2/ls /tmp/test2)
	@echo "Expected : "22$(shell /bin/ls /tmp/test)$(shell /bin/ls /tmp/test2)
	@exit 1
endif

	@echo -n "TEST 4: The In-fect-ception 2 ..."
	@cp /bin/echo /tmp/test/echo
	@cp /bin/echo /tmp/test2/echo
	@/tmp/test2/ls 1>/dev/null
ifeq ($(shell strings /tmp/test/* | grep Famine | wc -l)$(shell strings /tmp/test2/* | grep Famine | wc -l)$(shell /tmp/test/echo tutu)$(shell /tmp/test2/echo toto), 33$(shell /bin/echo tutu)$(shell /bin/echo toto))
	@echo " Passed !"
else
	@echo " Failed !"
	@echo "Got      : "$(shell strings /tmp/test/* | grep Famine | wc -l)$(shell strings /tmp/test2/* | grep Famine | wc -l)$(shell /tmp/test/echo tutu)$(shell /tmp/test2/echo toto)
	@echo "Expected : "33$(shell /bin/echo tutu)$(shell /bin/echo toto)
endif
