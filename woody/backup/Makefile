#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2018/05/08 14:07:56 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= woody_woodpacker

SRC_DIR	= srcs/
SRC		= main.c
#decrypt.c
#encrypt.c
SRC_A	=

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	SRC 	+= pack_macho.c
	SRC_A	+= woody_mach.s woody_mach_encrypt.s
	ASM		= ~/Downloads/nasm-2.11.02/nasm
	AFLAGS 	= -f macho64
endif
ifeq ($(UNAME_S), Linux)
	SRC 	+= pack_elf.c
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P), x86_64)
		SRC_A	+= woody_elf.s woody_elf_encrypt.s
		ASM		= nasm
		AFLAGS 	= -f elf64
	endif
endif

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

all: lib $(NAME)

$(NAME): $(OBJ) $(OBJ_A)
	$(WWW) -o $@ $^ $(LIBS) -fPIC
#	$(WWW) $(FLAGS) -o $(OBJ_DIR)file_info.o -c $(SRC_DIR)file_info.c $(INCLUDE)
#	$(WWW) -o hex $(OBJ_DIR)file_info.o $(LIBS) # !!!!

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
