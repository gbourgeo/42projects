#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/28 02:12:40 by gbourgeo          #+#    #+#              #
#    Updated: 2017/01/03 22:17:38 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= minishell

SRC		= main.c			\
			ft_minishell.c	\
			ft_env.c		\
			ft_free.c		\
			ft_fork.c		\
			ft_envcpy.c		\
			ft_env_options.c \
			ft_getenv.c		\
			ft_setenv.c		\
			ft_cd.c			\
			ft_cd_check.c	\
			ft_change_pwds.c\
			ft_getcwd.c		\
			ft_exit.c		\
			ft_unsetenv.c	\
			ft_stralnum.c 	\
			ft_split_whitespaces.c	\
			ft_strerror.c

OBJ_D 	= obj/

OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= $(LIBFT)includes/

all: $(LIBFT) $(OBJ_D) $(NAME)

.PHONY: $(LIBFT) clean fclean re

$(LIBFT):
	@make -C $@

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ) | $(LIBFT)
	gcc $(FLAGS) -o $@ $^ -L $(LIBFT) -lft

$(OBJ_D)%.o: %.c main.h | $(OBJ_D)
	gcc $(FLAGS) -o $@ -c $< -I $(LIBFT_H)

clean:
	@make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
