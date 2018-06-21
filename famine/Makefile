#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/21 00:34:49 by root             ###   ########.fr        #
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
LIBS	= -L $(LIB_DIR) -lft
LIB_DIR	= libft/
INCLUDE	= -I $(LIB_DIR)/includes
ASM		= nasm
ASMFLAG	= -f elf64 -O2

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@
	@make -C $(LIB_DIR)

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)

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

hex: re
	make -C $(LIB_DIR)
	$(WWW) -o hex srcs/elf/elf_file_info.c $(INCLUDE) $(LIBS)

test1: hex
	$(WWW) main.c obj/famine64.o $(INCLUDE)
	rm -rf /tmp/test/ /tmp/test2/
	mkdir -p /tmp/test/
	$(WWW) -o /tmp/test/elf64 -m64 Ressources/sample.c
	./a.out
	/tmp/test/elf64
	cp /bin/ls /tmp/test/.
	./a.out
	/tmp/test/ls
	cp /bin/cat /tmp/test/.
	cp /bin/echo /tmp/test/.
	./a.out
	/tmp/test/echo toto

test: hex
	@rm -rf /tmp/test /tmp/test2
	@mkdir -p /tmp/test /tmp/test2
	$(WWW) -o /tmp/test/elf64 -m64 Ressources/sample.c
	$(WWW) -o /tmp/test2/elf64 -m64 Ressources/sample.c

	@./$(NAME)
	@echo -n "TEST 1: The Infection ..."
ifneq ($(shell sleep 0.3 && strings /tmp/test/elf64 | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test/elf64 | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test/elf64 | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && strings /tmp/test2/elf64 | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test2/elf64 | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test/elf64), $(shell Ressources/elf64))
	@echo " Failed !"
	@echo "/tmp/test/elf64"
	@echo "Expected : "$(shell Ressources/elf64)
	@echo "Got      : "$(shell /tmp/test/elf64)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test2/elf64), $(shell Ressources/elf64))
	@echo " Failed !"
	@echo "/tmp/test2/elf64"
	@echo "Expected : "$(shell Ressources/elf64)
	@echo "Got      : "$(shell /tmp/test2/elf64)
	@exit 1
else
	@echo " Passed !"
endif

	@./$(NAME)
	@echo -n "TEST 2: No Re-Infection ..."
ifneq ($(shell sleep 0.3 && strings /tmp/test/elf64 | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test/elf64 | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test/elf64 | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && strings /tmp/test2/elf64 | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test2/elf64 | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test2/elf64 | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test/elf64), $(shell Ressources/elf64))
	@echo " Failed !"
	@echo "/tmp/test/elf64"
	@echo "Expected : "$(shell Ressources/elf64)
	@echo "Got      : "$(shell /tmp/test/elf64)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test2/elf64), $(shell Ressources/elf64))
	@echo " Failed !"
	@echo "/tmp/test2/elf64"
	@echo "Expected : "$(shell Ressources/elf64)
	@echo "Got      : "$(shell /tmp/test2/elf64)
	@exit 1
else
	@echo " Passed !"
endif

	@cp /bin/ls /tmp/test/ls
	@cp /bin/ls /tmp/test2/ls
	@/tmp/test/elf64 1>/dev/null
	@echo -n "TEST 3: The In-fect-ception ..."
ifneq ($(shell sleep 0.3 && strings /tmp/test/ls | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test/ls | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test/ls | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && strings /tmp/test2/ls | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test2/ls | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test2/ls | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test/ls), $(shell /bin/ls))
	@echo " Failed !"
	@echo "/tmp/test/ls"
	@echo "Expected : "$(shell /bin/ls)
	@echo "Got      : "$(shell /tmp/test/ls)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test2/ls -l srcs), $(shell /bin/ls -l srcs))
	@echo " Failed !"
	@echo "/tmp/test2/ls -l srcs"
	@echo "Expected : "$(shell /bin/ls -l srcs)
	@echo "Got      : "$(shell /tmp/test2/ls -l srcs)
	@exit 1
else
	@echo " Passed !"
endif

	@cp /bin/echo /tmp/test/echo
	@cp /bin/echo /tmp/test2/echo
	@/tmp/test2/ls 1>/dev/null
	@echo -n "TEST 4: The In-fect-ception 2 ..."
ifneq ($(shell sleep 0.3 && strings /tmp/test/echo | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test/echo | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test/echo | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && strings /tmp/test2/echo | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test2/echo | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test2/echo | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test/echo toto), $(shell /bin/echo toto))
	@echo " Failed !"
	@echo "/tmp/test/echo toto"
	@echo "Expected : "$(shell /bin/echo toto)
	@echo "Got      : "$(shell /tmp/test/echo toto)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test2/echo -n tutu), $(shell /bin/echo -n tutu))
	@echo " Failed !"
	@echo "/tmp/test2/echo -n tutu"
	@echo "Expected : "$(shell /bin/echo -n tutu)
	@echo "Got      : "$(shell /tmp/test2/echo -n tutu)
	@exit 1
else
	@echo " Passed !"
endif

	@cp /bin/bash /tmp/test/bash
	@cp /bin/bash /tmp/test2/bash
	@./$(NAME)
	@echo -n "TEST 5: The Bash Test ..."
ifneq ($(shell sleep 0.3 && strings /tmp/test/bash | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test/bash | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test/bash | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && strings /tmp/test2/bash | grep Famine | wc -l), 1)
	@echo " Failed !"
	@echo "strings /tmp/test2/bash | grep Famine | wc -l"
	@echo "Expected : "1
	@echo "Got      : "$(shell strings /tmp/test2/bash | grep Famine | wc -l)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test/bash -c ls), $(shell /bin/bash -c ls))
	@echo " Failed !"
	@echo "/tmp/test/bash -c ls"
	@echo "Expected : "$(shell /bin/bash -c ls)
	@echo "Got      : "$(shell /tmp/test/bash -c ls)
	@exit 1
else ifneq ($(shell sleep 0.3 && /tmp/test2/bash -c date), $(shell /bin/bash -c date))
	@echo " Failed !"
	@echo "/tmp/test2/bash -c date"
	@echo "Expected : "$(shell /bin/bash -c date)
	@echo "Got      : "$(shell /tmp/test2/bash -c date)
	@exit 1
else
	@echo " Passed !"
endif
