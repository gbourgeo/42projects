#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2018/07/19 03:34:19 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Durex
SRC		= main.c install.c durex.c server.c client.c encrypt.c commands.c quit.c
SRC		+= move.c
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRC_DIR	= srcs/
HDR_DIR = -I includes/ -I $(LIB_DIR)/includes/
OBJ_DIR	= objs/
LIB_DIR	= libft/
FLAGS	= -Wall -Werror -Wextra
LIBS	= -L$(LIB_DIR) -lft

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	make -C $(LIB_DIR)
	mkdir -p $@

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $< $(HDR_DIR)

clean:
	/bin/rm -rf $(OBJ_DIR)
#	make -C $(LIB_DIR) clean

fclean: clean
	/bin/rm -f $(NAME)
#	make -C $(LIB_DIR) fclean

re: fclean all

rm:
	service Durex stop
	rm /bin/Durex
	rm /etc/init.d/Durex
	rm /var/lock/durex.lock
