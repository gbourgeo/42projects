#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/08 17:52:49 by gbourgeo          #+#    #+#              #
#    Updated: 2018/07/09 20:37:03 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= whatever

SRCS	= whatever.cpp

OBJS	= $(SRCS:.cpp=.o)

FLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	clang++ -o $@ $^

%.o: %.cpp
	clang++ $(FLAGS) -c $<

clean:
	/bin/rm $(OBJS)

fclean: clean
	/bin/rm $(NAME)

re: fclean all
