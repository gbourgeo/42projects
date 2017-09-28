#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 22:31:28 by gbourgeo          #+#    #+#              #
#    Updated: 2017/09/28 18:46:20 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER = Matt_daemon

SERVER_D = server/

SERVER_S_D = $(SERVER_D)src/

SERVER_S = main.cpp Tintin.cpp Server.cpp Exceptions.cpp Daemonize.cpp

SERVER_H = -I $(SERVER_D)inc/

SERVER_O_D = $(SERVER_D)obj/

SERVER_O = $(addprefix $(SERVER_O_D), $(SERVER_S:.cpp=.o))


CLIENT = Ben_AFK

CLIENT_D = client/build-MainClient-Desktop_Qt_5_9_1_GCC_64bit-Debug/

CXX = g++

FLAGS = -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_O)
	$(CXX) $(FLAGS) -o $@ $^

$(SERVER_O_D)%.o: $(SERVER_S_D)%.cpp | prep
	$(CXX) $(FLAGS) -o $@ -c $< $(SERVER_H)

prep:
	@mkdir -p $(SERVER_O_D)

$(CLIENT):
	@make -C $(CLIENT_D)
	@cp $(CLIENT_D)MainClient ./$(CLIENT)

clean:
	/bin/rm -rf $(SERVER_O_D)
	make -C $(CLIENT_D) clean

fclean: clean
	/bin/rm -rf $(SERVER)
	/bin/rm -rf $(CLIENT)

re: fclean all
