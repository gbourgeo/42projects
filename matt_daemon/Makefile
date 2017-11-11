#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 22:31:28 by gbourgeo          #+#    #+#              #
#    Updated: 2017/11/11 23:30:41 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER = server
NAME = Matt_daemon
SERVER_DIR = Matt/
SERVER_SRC_DIR = $(SERVER_DIR)src/
SERVER_SRC = 	Main.cpp \
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
				base64.cpp \
				stdlib_func.cpp
SERVER_HDR_DIR = $(SERVER_DIR)inc/
SERVER_OBJ_DIR = $(SERVER_DIR)obj/
SERVER_OBJ = $(addprefix $(SERVER_OBJ_DIR), $(SERVER_SRC:.cpp=.o))


CLIENT = client
NAME_2 = Ben_AFK
CLIENT_DIR = Ben/


COMMON_DIR = Common/
COMMON_SRC = base64.cpp
COMMON_OBJ_DIR = $(SERVER_OBJ_DIR)
COMMON_OBJ = $(addprefix $(COMMON_OBJ_DIR), $(COMMON_SRC:.cpp=.o))


CXX = g++

FLAGS = -Wall -Werror -Wextra -std=c++11

SSL_LIBS = -L/usr/lib/x86_64-linux-gnu/ -lssl -lcrypto


all: $(SERVER) $(CLIENT)

$(SERVER): $(NAME)
$(NAME): $(SERVER_OBJ) $(COMMON_OBJ)
	$(CXX) $(FLAGS) -o $@ $^ $(SSL_LIBS)

$(SERVER_OBJ_DIR)%.o: $(SERVER_SRC_DIR)%.cpp $(SERVER_HDR_DIR)%.hpp $(COMMON_DIR)common.hpp
	@mkdir -p $(SERVER_OBJ_DIR)
	$(CXX) $(FLAGS) -o $@ -c $< -I $(SERVER_HDR_DIR) -I $(COMMON_DIR)

$(CLIENT): $(NAME_2)
$(NAME_2):
	@make -C $(CLIENT_DIR)

$(COMMON_OBJ_DIR)%.o: $(COMMON_DIR)%.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

clean:
	/bin/rm -rf $(SERVER_OBJ_DIR)
	make -C $(CLIENT_DIR) clean

fclean: clean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(NAME_2)

re: fclean all
