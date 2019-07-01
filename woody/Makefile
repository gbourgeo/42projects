#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2019/06/04 00:48:21 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= woody_woodpacker
ARCH	=
ifeq ($(BIT32), 1)
NAME	= woody_woodpacker32
ARCH	= -m32
endif

SRC_DIR	= srcs/
SRC		= main.c fatal.c key_generator.c

ELF_DIR	= $(SRC_DIR)elf/
MAC_DIR	= $(SRC_DIR)macho/

HDR_DIR	= includes/

OBJ_DIR	= obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_S	= $(addprefix $(OBJ_DIR), $(SRC_S:.s=.o))

UNAME_S	:= $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S), Linux)
SRC			+= check_elf_info.c pack_elf64.c pack_elf32.c
SRC_S		= woody64.s encrypt64.s
SRC_S		+= woody32.s encrypt32.s
ASM			= nasm
ASMFLAG		= -f elf64
ifeq ($(BIT32), 1)
ASMFLAG		= -f elf32
endif
endif

ifeq ($(UNAME_S), Darwin)
SRC			+= check_macho_info.c pack_macho64.c ft_swap_bytes.c
SRC_S		= woody64.s encrypt64.s
ASM			= nasm
ASMFLAG		= -f macho64
endif

LIB_DIR	= libft/
LIB_HDR	= $(LIB_DIR)includes

WWW 	= gcc $(ARCH)
FLAGS	= -Wall -Werror -Wextra
INCLUDE	= -I$(HDR_DIR) -I$(LIB_HDR)
LIBS	= -L$(LIB_DIR) -lft

all: lib $(NAME)

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)

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

.PHONY: lib clean fclean re

lib:
	@make ARCH=$(ARCH) -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	/bin/rm -f $(NAME)
	/bin/rm -f $(NAME)32
	/bin/rm -f woody
	/bin/rm -f hex
	/bin/rm -f elf32
	/bin/rm -f elf64
	/bin/rm -f macho64

re: fclean all

hex: lib
ifeq ($(UNAME_S), Linux)
	$(WWW) $(ARCH) -o hex Ressources/elf_file_info.c $(INCLUDE) $(LIBS)
else ifeq ($(UNAME_S), Darwin)
	$(WWW) -o hex Ressources/macho_file_info.c $(INCLUDE) $(LIBS)
endif

elf64:
	gcc -m64 -o elf64 Ressources/sample.c

elf32:
	gcc -m32 -o elf32 Ressources/sample.c

macho64:
	gcc -m64 -o macho64 Ressources/sample.c
