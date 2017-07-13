#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/13 13:35:58 by gbourgeo          #+#    #+#              #
#    Updated: 2017/07/13 13:43:17 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC_D = src/

SRC = ft_putchar.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_swap.c

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

WWW = gcc -Wall -Werror -Wextra

HDR_D = includes/

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	mkdir -p $@

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

$(OBJ_D)%.o: $(SRC_D)%.c
	$(WWW) -o $@ -c $< -I $(HDR_D)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
