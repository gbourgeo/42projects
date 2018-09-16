#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/23 16:47:51 by gbourgeo          #+#    #+#              #
#    Updated: 2013/12/30 01:04:09 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= push_swap

SRC		= main.c ft_push_swap.c \
			ps_swap.c ps_swap_list.c ps_newlist.c ps_goto_end.c is_l_sorted.c\
			ps_end_to_first.c ps_first_to_end.c ps_check_params.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= libft/includes/

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -o $(NAME) $(OBJ) -L $(LIBFT) -lft -O3

%.o: %.c
	gcc $(FLAGS) -c $^ -I $(LIBFT_H)

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIBFT)libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
