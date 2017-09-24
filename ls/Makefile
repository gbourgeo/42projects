#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                          +#+  +:+       +#+   #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/08 05:16:04 by gbourgeo                #+#    #+#        #
#    Updated: 2016/12/31 18:48:44 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

SRC_D = src/

SRC_H = includes/

SRC = main.c \
	ft_file_inf.c \
	ft_get_dir.c \
	ft_is_a_file.c \
	ft_ls_big_r.c \
	ft_ls_r.c \
	ft_perror.c \
	ft_print.c \
	ft_sort.c \
	ft_sort_by_last_change.c \
	ft_sort_by_file_creation.c \
	ft_sort_by_last_modif.c \
	ft_sort_by_last_access.c \
	ft_sort_by_file_size.c \
	ft_struct_init.c \
	ft_create.c \
	ft_clear.c \
	ft_ls_l.c \
	ft_print_long.c \
	ft_print_big_f.c \
	ft_calc_date.c \
	ft_exit.c

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

WWW = -Wall -Werror -Wextra

LIBFT = ../libft

HDR = $(LIBFT)/includes/

all: libft $(NAME)

.PHONY: all clean fclean re

libft:
	@make -C $(LIBFT)
	@mkdir -p $(OBJ_D)

$(NAME): $(OBJ)
	@gcc $(WWW) -o $(NAME) $(OBJ) -I $(HDR) -L $(LIBFT) -lft
	@echo "GENERATED: $(NAME)"

$(OBJ_D)%.o: $(SRC_D)%.c | $(SRC_H)main.h
	gcc $(WWW) -I $(HDR) -o $@ -c $^ -I $(SRC_H)

clean:
	@make -C $(LIBFT) clean
	rm -rf $(OBJ_D)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
