# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/15 05:31:47 by gbourgeo          #+#    #+#              #
#    Updated: 2019/08/02 22:56:36 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= hotrace

SRC_D	= srcs/
SRC		= hotrace.c ft_add_node.c ft_search_node.c ft_memalloc.c ft_putstr.c \
		ft_strjoin.c ft_strcmp.c get_next_line.c
OBJ_D	= objs/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))
INC_D	= includes/
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: begin $(NAME)

begin:
	@mkdir -p $(OBJ_D)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_D)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
