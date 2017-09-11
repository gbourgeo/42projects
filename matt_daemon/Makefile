#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 22:31:28 by gbourgeo          #+#    #+#              #
#    Updated: 2017/09/11 06:23:22 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Matt_daemon

SRC_D = src/

SRC = Main.cpp Daemon.cpp Tintin.cpp Server.cpp LaunchServer.cpp

OBJ_D = obj/

OBJ = $(addprefix $(OBJ_D), $(SRC:.cpp=.o))

HEADERS = includes

WWW = g++ -Wall -Werror -Wextra

all: prep $(NAME)

prep:
	@mkdir -p $(OBJ_D)

$(NAME): $(OBJ)
	$(WWW) -o $@ $^

$(OBJ_D)%.o: $(SRC_D)%.cpp
	$(WWW) -o $@ -c $< -I $(HEADERS)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
