#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/19 00:05:16 by root              #+#    #+#              #
#    Updated: 2018/09/16 10:19:22 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lemipc

SRC_D = src/

SRC = main.c 			\
	ft_atoull.c			\
	ft_create_join.c 	\
	ft_exit.c 			\
	ft_game.c			\
	ft_getenv.c			\
	ft_init.c			\
	ft_move.c			\
	ft_msg.c 			\
	ft_players.c		\
	ft_print_map.c		\
	ft_sem.c	 		\
	ft_signal.c 		\
	ft_strategy.c 		\
	ft_termcaps.c 		\
	ft_wait_players.c

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

LIBFT = libft/

HEADERS = -I includes -I $(LIBFT)includes

WWW = gcc -Wall -Werror -Wextra

all: preall $(NAME)

preall:
	@mkdir -p obj
	@make -C $(LIBFT)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^ -L $(LIBFT) -lft -lncurses

$(OBJ_D)%.o: $(SRC_D)%.c includes/lemipc.h
	$(WWW) -o $@ -c $< $(HEADERS)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
