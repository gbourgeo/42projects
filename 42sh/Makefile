#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/28 02:12:40 by gbourgeo          #+#    #+#              #
#    Updated: 2018/04/06 19:02:35 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= 42sh

SRC_DIR = srcs/
SRC		= ft_minishell.c	\
		check_and_exec.c	\
		ft_commands.c		\
		ft_error.c			\
		ft_fork.c			\
		ft_frees.c			\
		ft_get_path.c		\
		ft_history.c		\
		ft_init_shell.c		\
		ft_signals.c		\
		prompt.c			\
		termios_functions.c	\

BUILTINS_DIR	= builtins/
BUILTINS	= ft_cd.c			\
			ft_cd_check.c		\
			ft_change_pwds.c	\
			ft_echo.c			\
			ft_env.c			\
			ft_exit.c			\
			ft_getcwd.c			\
			ft_getenv.c			\
			ft_setenv.c			\
			ft_unsetenv.c

LIB2_DIR	= libft2/
LIB2	= ft_close.c			\
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
		ft_str2join.c

REDIREC_DIR	= redirections/
REDIREC	= ft_argsnew.c			\
		ft_lexical_analysis.c	\
		ft_parser.c				\
		ft_pipes_errors.c		\
		ft_separators_errors.c	\
		ft_syntax_analysis.c

PIPEX_DIR	= pipex/
PIPEX	= ft_pipe_left.c	\
		ft_pipe_pipe.c		\
		ft_pipe_rights.c	\
		ft_pipex_or_exec.c

KEY_DIR = keyboard/
KEYS	= ft_key_control.c	\
		ft_key_search.c		\
		ft_key_suppr.c		\
		ft_normal_keys.c

OBJ_DIR = obj/
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_BUI = $(addprefix $(OBJ_DIR), $(BUILTINS:.c=.o))
OBJ_LIB = $(addprefix $(OBJ_DIR), $(LIB2:.c=.o))
OBJ_RED = $(addprefix $(OBJ_DIR), $(REDIREC:.c=.o))
OBJ_PIP = $(addprefix $(OBJ_DIR), $(PIPEX:.c=.o))
OBJ_KEY	= $(addprefix $(OBJ_DIR), $(KEYS:.c=.o))

FLAGS	= -Wall -Werror -Wextra

LIBFT	= libft/

INCLUDES = -I includes -I $(LIBFT)/includes -I /usr/include

LIBRAIRIES = -L$(LIBFT) -lft -ltermcap -g3

all: imsexyandiknowit $(NAME)

.PHONY: clean fclean re all make

imsexyandiknowit:
	@make -C $(LIBFT)
	@mkdir -p obj
	@echo -n - Compilation du Shell42

$(NAME): $(OBJ) $(OBJ_BUI) $(OBJ_LIB) $(OBJ_RED) $(OBJ_PIP) $(OBJ_KEY)
	@gcc -o $@ $^ $(LIBRAIRIES)
	@echo "      Enjoy!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo -n .
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

$(OBJ_DIR)%.o: $(BUILTINS_DIR)%.c
	@echo -n .
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

$(OBJ_DIR)%.o: $(LIB2_DIR)%.c
	@echo -n .
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

$(OBJ_DIR)%.o: $(REDIREC_DIR)%.c
	@echo -n .
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

$(OBJ_DIR)%.o: $(PIPEX_DIR)%.c
	@echo -n .
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

$(OBJ_DIR)%.o: $(KEY_DIR)%.c
	@echo -n .
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT) fclean
	rm -rf $(NAME)

re: fclean all
