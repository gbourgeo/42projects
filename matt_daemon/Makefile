#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 22:31:28 by gbourgeo          #+#    #+#              #
#    Updated: 2017/10/22 15:47:14 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER = server

NAME = Matt_daemon

SERVER_D = Matt/

SERVER_S_D = $(SERVER_D)src/

SERVER_S = 	Main.cpp \
			Tintin.cpp \
			Server.cpp \
			daemonLogs.cpp \
			daemonInfo.cpp \
			machineInfo.cpp \
			serviceInfo.cpp \
			mail.cpp \
			Exceptions.cpp \
			Daemonize.cpp \
			getSocket.cpp \
			stdlib_func.cpp

SERVER_H_D = $(SERVER_D)inc/

SERVER_O_D = $(SERVER_D)obj/

SERVER_O = $(addprefix $(SERVER_O_D), $(SERVER_S:.cpp=.o))


CLIENT = client

NAME_2 = Ben_AFK

CLIENT_D = Ben/

CXX = g++

FLAGS = -Wall -Werror -Wextra -std=c++11

SSL_LIBS = -L/usr/lib/x86_64-linux-gnu/ -lssl -lcrypto

all: $(SERVER) #$(CLIENT)

$(SERVER): $(NAME)

$(NAME): $(SERVER_O)
	$(CXX) $(FLAGS) -o $@ $^ $(SSL_LIBS)

$(SERVER_O_D)%.o: $(SERVER_S_D)%.cpp $(SERVER_H_D)%.hpp
	@mkdir -p $(SERVER_O_D)
	$(CXX) $(FLAGS) -o $@ -c $< -I $(SERVER_H_D)

$(CLIENT): $(NAME_2)

$(NAME_2):
	@make -C $(CLIENT_D)

clean:
	/bin/rm -rf $(SERVER_O_D)
#	make -C $(CLIENT_D) clean

fclean: clean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(NAME_2)

re: fclean all
