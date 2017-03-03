#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/28 02:12:40 by gbourgeo          #+#    #+#              #
#    Updated: 2017/03/03 07:31:04 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= 21sh

SRC_D 	= src/

HDR		= includes/

SRC		= main.c					\
			check_and_exec.c		\
			copy_command.c			\
			ctrl_command.c			\
			ctrl_shft_command.c		\
			cursor.c				\
			dollar.c				\
			expansions.c			\
			historic_command.c		\
			historic_functions.c	\
			historic_updates.c		\
			init_signals.c			\
			init_termcaps.c			\
			k_home_end.c			\
			keypad_command.c		\
			lexical_analysis.c		\
			parse_command.c			\
			pipes.c					\
			pipes_loop.c			\
			pos_function.c			\
			prompt.c				\
			read_command.c			\
			rewrite_cmd_prpt.c		\
			split_command.c			\
			shift_command.c			\
			tab_command.c			\
			tab_functions.c			\
			treat_command.c			\
			ft_cd.c					\
			ft_cd_check.c			\
			ft_change_pwds.c		\
			ft_echo.c				\
			ft_env.c				\
			ft_env_options.c 		\
			ft_env_check.c			\
			ft_env_extra.c			\
			ft_envcpy.c				\
			ft_exit.c				\
			ft_fork.c				\
			ft_free.c				\
			ft_getcwd.c				\
			ft_getenv.c				\
			ft_insert_str.c			\
			ft_iswhitespace.c		\
			ft_minishell.c			\
			ft_put2endl_fd.c		\
			ft_realloc.c			\
			ft_setenv.c				\
			ft_split_whitespaces.c	\
			ft_stralnum.c 			\
			ft_strerror.c			\
			ft_termcaps.c			\
			ft_unsetenv.c

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

$(NAME): $(OBJ) | $(LIBFT_A)
	@$(FLAGS) -o $@ $^ -L $(LIBFT) -lft -ltermcap
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
