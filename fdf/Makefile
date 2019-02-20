#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/18 13:43:18 by gbourgeo          #+#    #+#              #
#    Updated: 2018/12/15 07:22:16 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= fdf

SRC_D	= srcs/
OBJ_D	= objs/
INC_D	= include/
LIB_D	= libft/

SRC		= main.c			\
		get_map.c			\
		get_next_line.c		\
		ft_free.c			\
		get_coord.c			\
		ft_strangesplit.c	\
		fdf.c				\
		ft_draw.c			\
		ft_draw_parallel.c	\
		ft_draw_isometric.c	\
		ft_draw_conic.c		\
		ft_put_color.c		\
		key_hook_func.c		\
		ft_clear_image.c	\
		ft_draw_cases.c		\
		ft_abs.c			\
		ft_pow.c			\

OBJ		= $(addprefix $(OBJ_D), $(SRC:.c=.o))

FLAGS	= -Wall -Werror -Wextra

LIBS	= -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
LIBS	+= -L libft/ -lft

INCS	= -I /usr/X11/$(INC_D) -I libft/$(INC_D) -I $(INC_D)

all: $(LIB_D) $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ)
	@make -C $(LIB_D)
	gcc -o $@ $^ $(LIBS)

$(OBJ_D)%.o: $(SRC_D)%.c
	gcc $(FLAGS) -o $@ -c $< $(INCS)

clean:
	@make -C $(LIB_D) clean
	rm -rf $(OBJ_D)

fclean: clean
	@make -C $(LIB_D) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
