#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/26 12:25:22 by root              #+#    #+#              #
#    Updated: 2017/04/18 00:02:40 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_traceroute

SRC_D = src/

SRC = ft_traceroute.c	\
	ft_atod.c			\
	ft_err.c			\
	ft_getaddr.c		\
	ft_init.c			\
	ft_loop.c			\
	ft_options.c		\
	ft_parse_reply.c	\
	ft_print.c			\
	ft_recv.c			\
	ft_send.c			\
	ft_usage.c

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.c=.o))

LIB_D = libft

HEADERS = -I includes -I $(LIB_D)/includes

WWW = gcc -Wall -Werror -Wextra

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	make -C $(LIB_D)
	mkdir -p $(OBJ_D)

$(NAME): $(OBJ)
	$(WWW) -o $(NAME) $^ -L $(LIB_D) -lft

$(OBJ_D)%.o: $(SRC_D)%.c includes/ft_traceroute.h
	$(WWW) -o $@ -c $< $(HEADERS)

clean:
	make -C $(LIB_D) clean
	rm -rf $(OBJ_D)

fclean: clean
	make -C $(LIB_D) fclean
	rm -f $(NAME)

re: fclean all
