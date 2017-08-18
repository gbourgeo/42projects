#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/05 01:54:08 by gbourgeo          #+#    #+#              #
#    Updated: 2017/08/17 20:02:07 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SRC_DIR = src/

SRC = ft_printf.c		\
	ft_strtoupper.c 	\
	ft_itoa_base.c		\
	ft_atouc.c			\
	pf_s.c				\
	pf_p.c				\
	pf_di.c				\
	pf_o.c				\
	pf_u.c				\
	pf_x.c				\
	pf_c.c				\
	pf_percent.c		\
	pf_writes.c			\
	pf_wchar.c

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_DIR = libft/

LIB = ft_isdigit.c ft_memset.c ft_putnbr.c ft_strchr.c ft_strdup.c ft_strjoin.c\
	ft_strlen.c ft_strnew.c ft_putchar.c ft_strcat.c ft_strcpy.c ft_memcpy.c\
	ft_bzero.c ft_pow.c

LIB_OBJ = $(addprefix $(OBJ_DIR), $(LIB:.c=.o))

HEADER = -I includes/ -I libft/includes

WWW = gcc -Wall -Werror -Wextra -std=c99

all: $(NAME)

$(NAME): $(OBJ) $(LIB_OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo CREATED: $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(WWW) -o $@ -c $< $(HEADER)

$(OBJ_DIR)%.o: $(LIB_DIR)%.c
	@$(WWW) -o $@ -c $< $(HEADER)

clean:
	@make -C $(LIB_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@if test -f a.out ; then /bin/rm a.out; fi
	/bin/rm -f $(NAME)

re: fclean all

test: re
	gcc ../main.c $(HEADER) -L. -lftprintf && ./a.out
