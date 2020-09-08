#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/28 12:09:42 by root              #+#    #+#              #
#    Updated: 2018/06/29 21:24:56 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = logger

SRCS = main.cpp Logger.cpp

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
	/bin/rm *.log

re: fclean all
