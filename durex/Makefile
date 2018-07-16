#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2018/07/16 23:41:39 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Durex
SRC		= main.c install.c durex.c server.c client.c encrypt.c commands.c quit.c
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRC_DIR	= srcs/
HDR_DIR = includes/
OBJ_DIR	= objs/

FLAGS	= -Wall -Werror -Wextra

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(HDR_DIR)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

rm:
	service Durex stop
	rm /bin/Durex
	rm /etc/init.d/Durex
	rm /var/lock/durex.lock
