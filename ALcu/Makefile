# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naminei <naminei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/09 16:39:59 by gbourgeo          #+#    #+#              #
#    Updated: 2019/08/02 10:40:05 by naminei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= puissance4

SRC_D	= srcs/
SRC		= main.c				\
		ft_check_for_a_winner.c	\
		ft_ingame_checks.c		\
		ft_moves.c				\
		ft_play.c				\
		ft_print_board.c		\
		ft_termcaps.c			\
		checkarg.c				\
		error.c

INC_D	= includes/

OBJ_D	= objs/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

CC		= gcc
FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/
INCLUDES	= -I$(INC_D) -I$(LIBFT)includes/
LIBRARIES	= -L$(LIBFT) -lft -lncurses

.PHONY: clean fclean re all

all: preface $(NAME)

preface:
	@make -C $(LIBFT)
	@mkdir -p objs

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LIBRARIES)

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
