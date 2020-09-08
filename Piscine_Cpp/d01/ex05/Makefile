#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/28 12:09:42 by root              #+#    #+#              #
#    Updated: 2018/06/29 15:44:35 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = bob

SRCS = main.cpp Human.cpp Brain.cpp

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
