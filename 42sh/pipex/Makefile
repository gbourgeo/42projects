#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/21 02:22:13 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/27 19:43:20 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libpipe.a

SRC	= ft_pipex_or_exec.c	\
	ft_pipe_pipe.c			\
	ft_pipe_rights.c		\
	ft_pipe_left.c

OBJ = $(SRC:.c=.o)

WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re message

all: $(NAME)

$(NAME): message $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo " OK"

%.o: %.c
	@gcc $(WWW) -c $^ -I..
	@echo -n .

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

message:
	@echo -n - Compilation des Redirections2
