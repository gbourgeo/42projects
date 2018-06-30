#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/11 04:39:05 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/30 22:30:37 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= woody_woodpacker

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
SRC			+= get_elf_info.c pack_elf64.c pack_elf32.c
SRC_S		= woody64.s encrypt64.s woody32.s encrypt32.s
ASM			= nasm
ASMFLAG		= -f elf64
PRINT_HEX	= $(WWW) -o hex $(ELF_DIR)elf_file_info.c $(INCLUDE) $(LIBS)
endif
ifeq ($(UNAME_S), Darwin)
SRC			+= get_macho_info.c pack_macho64.c ft_swap_bytes.c
SRC_S		= woody64.s encrypt64.s
ASM			= ~/Downloads/nasm-2.11.02/nasm
ASMFLAG		= -f macho64
PRINT_HEX	= $(WWW) -o hex $(MAC_DIR)macho_file_info.c $(INCLUDE) $(LIBS)
endif

LIB_DIR	= libft/
LIB_HDR	= $(LIB_DIR)includes

WWW 	= gcc
FLAGS	= -Wall -Werror -Wextra
INCLUDE	= -I$(HDR_DIR) -I$(LIB_HDR)
LIBS	= -L$(LIB_DIR) -lft

all: lib $(NAME)

$(NAME): $(OBJ) $(OBJ_S)
	$(WWW) -o $@ $^ $(LIBS)
	$(PRINT_HEX)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

ifeq ($(UNAME_S), Linux)
$(OBJ_DIR)%.o: $(ELF_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(ELF_DIR)%.s
	$(ASM) $(ASMFLAG) -o $@ -g $<
endif

ifeq ($(UNAME_S), Darwin)
$(OBJ_DIR)%.o: $(MAC_DIR)%.c
	$(WWW) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_DIR)%.o: $(MAC_DIR)%.s
	$(ASM) $(ASMFLAG) -o $@ $<
endif

.PHONY: lib clean fclean re

lib:
	@make -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	/bin/rm -f woody
	/bin/rm -f $(NAME)
	/bin/rm -f hex

re: fclean all
