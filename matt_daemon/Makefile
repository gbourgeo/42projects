#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 22:31:28 by gbourgeo          #+#    #+#              #
#    Updated: 2017/09/28 00:38:51 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER = Matt_daemon

CLIENT = Ben_AFK

SRC_SERVER = MainServer.cpp Tintin.cpp Server.cpp Exceptions.cpp Daemonize.cpp

SERVER_D = server/

CLIENT_D = client/build-MainClient-Desktop_Qt_5_9_1_GCC_64bit-Debug/

OBJ_D = obj/

OBJ_SERVER = $(addprefix $(OBJ_D), $(SRC_SERVER:.cpp=.o))

SERVER_H = -I ./includes/

WWW = g++ -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(WWW) -o $@ $^

$(OBJ_D)%.o: $(SERVER_D)%.cpp | prep
	$(WWW) -o $@ -c $< $(SERVER_H)

$(CLIENT):
	@make -C $(CLIENT_D)
	@mv $(CLIENT_D)MainClient ./$(CLIENT)

prep:
	@mkdir -p $(OBJ_D)

clean:
	/bin/rm -rf $(OBJ_D)
	make -C $(CLIENT_D) clean

fclean: clean
	/bin/rm -rf $(SERVER)
	/bin/rm -rf $(CLIENT)

re: fclean all
