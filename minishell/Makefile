#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/28 02:12:40 by gbourgeo          #+#    #+#              #
#    Updated: 2018/10/26 09:18:26 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= minishell

SRC_D 	= src/
HDR		= includes/
SRC		= main.c			\
		check_and_exec.c	\
		ft_dollar.c	 		\
		ft_tilde.c	 		\
		ft_fatal.c			\
		ft_minishell.c		\
		ft_echo.c			\
		ft_env.c			\
		ft_fork.c			\
		ft_envdup.c			\
		ft_env_options.c 	\
		ft_env_check.c		\
		ft_env_extra.c		\
		ft_getenv.c			\
		ft_setenv.c			\
		ft_signal.c			\
		ft_cd.c				\
		ft_cd_check.c		\
		ft_change_pwds.c	\
		ft_exit.c			\
		ft_unsetenv.c		\
		ft_stralnum.c 		\
		ft_split_whitespaces.c	\
		ft_strerror.c

OBJ_D 	= obj/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

FLAGS	= -Wall -Werror -Wextra
LIBFT	= libft/
LIBFT_H	= $(LIBFT)includes/
LIBFT_A	= $(LIBFT)libft.a

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@make -C $(LIBFT)
	@mkdir -p $@

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $@ $^ -L $(LIBFT) -lft
	@echo "CREATED:" $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(HDR)main.h
	gcc $(FLAGS) -o $@ -c $< -I $(LIBFT_H) -I $(HDR)

.PHONY: clean fclean re

clean:
	@make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
