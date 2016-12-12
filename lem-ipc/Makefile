#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/19 00:05:16 by root              #+#    #+#              #
#    Updated: 2016/12/12 12:12:12 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lemipc

SRC_D = src/

SRC = main.c ft_exit.c ft_signal.c ft_create_join.c ft_init_sem.c ft_loop.c \
		ft_termcaps.c

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

LIBFT = libft/

LIBFTH = $(LIBFT)includes

WWW = gcc -Wall -Werror -Wextra

all: preall $(NAME)

preall:
	mkdir -p obj
	make -C $(LIBFT)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ -L $(LIBFT) -lft -lncurses

$(OBJ_D)%.o: $(SRC_D)%.c $(SRC_D)lemipc.h
	$(WWW) -o $@ -c $< -I $(LIBFTH)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
