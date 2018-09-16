#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/21 23:22:22 by gbourgeo          #+#    #+#              #
#    Updated: 2014/01/26 18:54:23 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= filler

SRC		= main.c		\
		get_next_line.c	\
		gets.c			\
		ft_start_program.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= libft/includes/

all: $(NAME)

$(NAME): message $(OBJ)
	@echo
	@make -C libft/
	@gcc -o $(NAME) $(OBJ) -L $(LIBFT) -lft -O3

%.o: %.c
	@echo -n .
	@gcc $(FLAGS) -c $(SRC) -I $(LIBFT_H)

clean:
	@make -C $(LIBFT) clean
	@echo - $(NAME)/ .o erased !
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@echo - $(NAME) erased !
	@rm -f $(NAME)

re: fclean all

message:
	@echo -n - Compilation de $(NAME)

.PHONY: clean fclean re all
