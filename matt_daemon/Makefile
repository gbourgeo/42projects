#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 22:31:28 by gbourgeo          #+#    #+#              #
#    Updated: 2017/09/25 07:33:03 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER = Matt_daemon

CLIENT = Ben_AFK

SRC_SERVER = MainServer.cpp Tintin.cpp Server.cpp Exceptions.cpp Daemonize.cpp

SRC_CLIENT = MainClient.cpp

SERVER_D = server/

CLIENT_D = client/

OBJ_D = obj/

OBJ_SERVER = $(addprefix $(OBJ_D), $(SRC_SERVER:.cpp=.o))

OBJ_CLIENT = $(addprefix $(OBJ_D), $(SRC_CLIENT:.cpp=.o))

HEADERS = ./includes/

WWW = g++ -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(WWW) -o $@ $^

$(OBJ_D)%.o: $(SERVER_D)%.cpp | prep
	$(WWW) -o $@ -c $< -I $(HEADERS)

$(CLIENT): $(OBJ_CLIENT)
	$(WWW) -o $@ $^

$(OBJ_D)%.o: $(CLIENT_D)%.cpp | prep
	$(WWW) -o $@ -c $< -I $(HEADERS)

prep:
	@mkdir -p $(OBJ_D)

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -rf $(SERVER)
	/bin/rm -rf $(CLIENT)

re: fclean all
