#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/28 02:12:40 by gbourgeo          #+#    #+#              #
#    Updated: 2018/10/20 16:41:09 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= minishell

SRC_D 	= src/

HDR		= includes/

SRC		= main.c			\
		check_and_exec.c	\
		ft_expansions.c 	\
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
		ft_cd.c				\
		ft_cd_check.c		\
		ft_change_pwds.c	\
		ft_getcwd.c			\
		ft_exit.c			\
		ft_unsetenv.c		\
		ft_stralnum.c 		\
		ft_split_whitespaces.c	\
		ft_strerror.c

OBJ_D 	= obj/

OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

FLAGS	= gcc -Wall -Werror -Wextra

LIBFT	= libft/

LIBFT_H	= $(LIBFT)includes/

LIBFT_A	= $(LIBFT)libft.a

all: $(LIBFT) $(OBJ_D) $(NAME)

.PHONY: $(LIBFT) clean fclean re

$(LIBFT):
	@make -C $@

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIBFT_A)
	@$(FLAGS) -o $@ $^ -L $(LIBFT) -lft
	@echo "CREATED:" $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(HDR)main.h | $(OBJ_D)
	$(FLAGS) -o $@ -c $< -I $(LIBFT_H) -I $(HDR)

clean:
	@make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
