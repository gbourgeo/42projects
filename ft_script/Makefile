#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/23 22:20:08 by gbourgeo          #+#    #+#              #
#    Updated: 2016/05/26 06:16:40 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_script

SRC = main.c \
	ft_env.c \
	ft_error.c \
	ft_execve.c \
	ft_fork.c \
	ft_get_path.c \
	ft_start_script.c \
	ft_term.c

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT = libft

LIBH = $(LIBFT)/includes

WWW = gcc -Wall -Werror -Wextra

all: lib $(NAME)

lib:
	@make -C $(LIBFT)
	@if ! test -d $(OBJ_DIR); then mkdir -p $(OBJ_DIR); echo mkdir -p $(OBJ_DIR); fi

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ -L $(LIBFT) -lft -I.

$(OBJ_DIR)%.o: %.c main.h
	$(WWW) -o $@ -c $< -I $(LIBH)

clean:
	@make -C $(LIBFT) clean
	@if test -d $(OBJ_DIR); then /bin/rm -rf $(OBJ_DIR); echo rm -rf $(OBJ); fi

fclean: clean
	@make -C $(LIBFT) fclean
	@if test -f $(NAME); then /bin/rm -f $(NAME); echo rm -f $(NAME); fi

re: fclean all

.PHONY: clean fclean re all