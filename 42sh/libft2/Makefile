#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/03 07:38:41 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/27 07:24:33 by gsaynac          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libft2.a

SRC		= get_next_line.c		\
		ft_close.c				\
		ft_deletechar.c			\
		ft_dup2.c				\
		ft_open.c				\
		ft_print_tables.c		\
		ft_realloc.c			\
		ft_split.c				\
		ft_split_whitespaces.c	\
		ft_strcdup.c			\
		ft_strcharset.c			\
		ft_stricpy.c			\
		ft_strndup.c			\
		ft_strerror.c			\
		ft_strrcdup.c			\
		ft_tabdup.c				\
		ft_tablen.c				\
		ft_str2join.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT_H	= ../libft/includes

.PHONY: clean fclean re all message

all: $(NAME)

$(NAME): message $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo " OK"

%.o: %.c
	@gcc $(FLAGS) -c $^ -I $(LIBFT_H) -I ./
	@echo -n .

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

message:
	@echo -n - Compilation de la libft2
