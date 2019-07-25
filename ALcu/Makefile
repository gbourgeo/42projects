#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/09 16:39:59 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/10 06:14:35 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= puissance4

SRC		= main.c	\
		ft_check_for_a_winner.c	\
		ft_player_moves.c	\
		ft_computer_moves.c	\
		ft_ingame_checks.c	\
		checkarg.c	\
		ft_play.c	\
		error.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= libft/includes/

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	gcc -o $(NAME) $(OBJ) -L $(LIBFT) -lft -O3

%.o: %.c
	@echo -n .
	gcc $(FLAGS) -c $(SRC) -I $(LIBFT_H)

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
