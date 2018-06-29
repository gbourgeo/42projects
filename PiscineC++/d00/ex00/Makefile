#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/28 12:09:42 by root              #+#    #+#              #
#    Updated: 2018/06/28 12:25:27 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = megaphone

SRCS = megaphone.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	clang++ -o $@ $<

%.o: %.cpp
	clang++ $(FLAGS) -o $@ -c $^

clean:
	/bin/rm -rf $(OBJS)

fclean: clean
	/bin/rm $(NAME)

re: fclean all
