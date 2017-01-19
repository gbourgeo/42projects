#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/03 07:46:01 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/13 23:30:07 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libbuiltins.a

SRC		= ft_cd.c	\
		ft_cd_check.c		\
		ft_change_pwds.c	\
		ft_echo.c	\
		ft_env.c	\
		ft_exit.c	\
		ft_getcwd.c	\
		ft_getenv.c	\
		ft_setenv.c	\
		ft_unsetenv.c

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
	@echo -n - Compilation des Builtins
