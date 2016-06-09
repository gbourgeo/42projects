#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/01 03:10:34 by gbourgeo          #+#    #+#              #
#    Updated: 2016/05/27 12:01:26 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

SRC = ft_end.c \
	ft_free.c \
	get_map.c \
	get_next_line.c \
	main.c \
	draw.c \
	ft_raycast.c \
	move.c \
	wolf.c

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT = libft

HDR = $(LIBFT)/includes

LIBX = /usr/local/lib -lmlx -framework OpenGL -framework AppKit

HDR_X = /usr/local/include/

WWW = gcc -Wall -Werror -Wextra

all: lib $(NAME)

lib:
	@make -C $(LIBFT)
	@if ! test -d $(OBJ_DIR); then mkdir -p $(OBJ_DIR); echo mkdir -p $(OBJ_DIR); fi

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ -L $(LIBX) -L $(LIBFT) -lft

$(OBJ_DIR)%.o: %.c
	$(WWW) -o $@ -c $^ -I $(HDR) -I $(HDR_X)

clean:
	@make -C $(LIBFT) clean
	@if test -d $(OBJ_DIR); then /bin/rm -rf $(OBJ_DIR); echo rm -f $(OBJ); fi

fclean: clean
	@make -C $(LIBFT) fclean
	@if test -f $(NAME); then /bin/rm -f $(NAME); echo rm -f $(NAME); fi

re: fclean all

.PHONY: clean fclean re
