#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/02 03:43:52 by gbourgeo          #+#    #+#              #
#    Updated: 2018/11/19 18:17:10 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= ft_select

SRC_D	= srcs/
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

OBJ_D	= objs/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

LIBFT	= libft/

LIBS	= -L$(LIBFT) -lft -ltermcap

FLAGS	= -Wall -Werror -Wextra

HDRS	= -Iincludes/ -I$(LIBFT)includes

all: $(OBJ_D) libft.a $(NAME)

$(OBJ_D):
	@mkdir -p $@

libft.a:
	@make -C libft/

$(NAME): $(OBJ)
	@gcc -o $@ $^ $(LIBS)
	@echo $(NAME) compiled !

$(OBJ_D)%.o: $(SRC_D)%.c
	gcc $(FLAGS) -o $@ -c $< $(HDRS)

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ_D)
	@echo "- "$(NAME)"/ .o erased !"

fclean: clean
	@rm -f $(LIBFT)libft.a
	@rm -f $(NAME)
	@echo "- libft.a & "$(NAME)" erased !"

re: fclean all

.PHONY: clean fclean re all
