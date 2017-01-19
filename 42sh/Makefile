#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/28 02:12:40 by gbourgeo          #+#    #+#              #
#    Updated: 2014/03/29 20:00:40 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= 42sh

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

KEYS	= keyboard/ft_key_control.c	\
		keyboard/ft_key_search.c	\
		keyboard/ft_key_suppr.c		\
		keyboard/ft_normal_keys.c

OBJ		= $(SRC:.c=.o)
OBJ2	= $(KEYS:.c=.o)

FLAGS	= -Wall -Werror -Wextra

BUILTIN	= builtins/

LIBFT2	= libft2/

REDIREC	= redirections/

PIPES	= pipex/

KEYS_D	= keyboard/

LIBFT	= libft/

LIBFT_H	= libft/includes/

all: imsexyandiknowit $(NAME)

.PHONY: clean fclean re all make

imsexyandiknowit:
	@make -C $(LIBFT)
	@make -C $(LIBFT2)
	@make -C $(BUILTIN)
	@make -C $(REDIREC)
	@make -C $(PIPES)
	@make -C $(KEYS_D)

$(NAME): message $(OBJ) 
	@gcc -o $(NAME) $(OBJ) $(OBJ2) -L $(BUILTIN) -lbuiltins \
	-L $(REDIREC) -lredirec -L $(LIBFT2) -lft2 -L $(LIBFT) -L $(PIPES) -lpipe \
	-lft -ltermcap -g3
	@echo "      Enjoy!"

%.o: %.c
	@gcc $(FLAGS) -c $^ -I/usr/include/
	@echo -n .

clean:
	@make -C $(LIBFT) clean
	@make -C $(LIBFT2) clean
	@make -C $(BUILTIN) clean
	@make -C $(REDIREC) clean
	@make -C $(PIPES) clean
	@make -C $(KEYS_D) clean
	rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@make -C $(LIBFT2) fclean
	@make -C $(BUILTIN) fclean
	@make -C $(REDIREC) fclean
	@make -C $(PIPES) fclean
	@make -C $(KEYS_D) fclean
	rm -f $(NAME)

re: fclean all

message:
	@echo -n - Compilation du Shell42
