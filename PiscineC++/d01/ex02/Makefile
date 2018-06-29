#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/28 12:09:42 by root              #+#    #+#              #
#    Updated: 2018/06/29 13:08:45 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = zombie

SRCS = main.cpp Zombie.cpp ZombieEvent.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	clang++ -o $@ $^

%.o: %.cpp
	clang++ $(FLAGS) -o $@ -c $< -I.

clean:
	/bin/rm -rf $(OBJS)

fclean: clean
	/bin/rm $(NAME)

re: fclean all
