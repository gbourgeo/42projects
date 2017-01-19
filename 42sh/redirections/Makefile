#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/03 14:53:34 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/26 08:56:35 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libredirec.a

SRC		= ft_argsnew.c			\
		ft_lexical_analysis.c	\
		ft_parser.c				\
		ft_pipes_errors.c		\
		ft_separators_errors.c	\
		ft_syntax_analysis.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

.PHONY: clean fclean re all message

all: $(NAME)

$(NAME): message $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo " OK"

%.o: %.c
	@gcc $(FLAGS) -c $^ -I ..
	@echo -n .

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

message:
	@echo -n - Compilation des Redirections
