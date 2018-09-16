#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/02 03:43:52 by gbourgeo          #+#    #+#              #
#    Updated: 2014/01/19 22:01:05 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= ft_select

SRC		= ft_select.c		\
			ft_color.c		\
			ft_delete.c		\
			ft_error.c		\
			ft_exit.c		\
			ft_init_list.c	\
			ft_load_new_capacities.c \
			ft_print_args.c	\
			ft_retur.c		\
			ft_signals.c	\
			ft_tgetinfo.c	\
			key_functions.c	\
			termios_functions.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= libft/includes/

all: $(NAME)

$(NAME): message $(OBJ)
	@echo
	@make -C libft/
	@gcc -o $(NAME) $(OBJ) -L $(LIBFT) -lft -O3 -ltermcap

%.o: %.c
	@echo -n .
	@gcc $(FLAGS) -c $(SRC) -I $(LIBFT_H)

clean:
	@make -C $(LIBFT) clean
	@rm -f $(OBJ)
	@echo "- "$(NAME)"/ .o erased !"

fclean: clean
	@rm -f $(LIBFT)libft.a
	@rm -f $(NAME)
	@echo "- libft.a & "$(NAME)"(.out) erased !"

re: fclean all

message:
	@echo -n - Compilation du projet

.PHONY: clean fclean re all
