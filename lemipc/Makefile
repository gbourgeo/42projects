# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naminei <naminei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/19 00:05:16 by root              #+#    #+#              #
#    Updated: 2019/07/07 14:38:37 by naminei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lemipc

SRC_D = src/

SRC = main.c 			\
	ft_atoull.c			\
	ft_create.c			\
	ft_exit.c 			\
	ft_exit_child.c 	\
	ft_game.c			\
	ft_getenv.c			\
	ft_init.c			\
	ft_join.c			\
	ft_move.c			\
	ft_msg.c 			\
	ft_players.c		\
	ft_print_map.c		\
	ft_sem.c	 		\
	ft_signal.c 		\
	ft_strategy.c 		\
	ft_termcaps.c 		\
	ft_wait_players.c

INC_D = includes/

DEPS = $(INC_D)lemipc.h

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

LIBFT = libft/

HEADERS = -I $(INC_D) -I $(LIBFT)includes

WWW = gcc -Wall -Werror -Wextra

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@
	@make -C $(LIBFT)

$(NAME): $(OBJ)
	gcc -o $@ $^ -L $(LIBFT) -lft -lncurses

$(OBJ_D)%.o: $(SRC_D)%.c $(DEPS)
	$(WWW) -o $@ -c $< $(HEADERS)

.PHONY: clean fclean re

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
