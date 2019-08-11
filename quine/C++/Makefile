# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/16 18:53:45 by gbourgeo          #+#    #+#              #
#    Updated: 2019/08/11 04:41:27 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Colleen
NAME2 = Grace
NAME3 = Sully

SRCS = Colleen.cpp
SRCS2 = Grace.cpp
SRCS3 = Sully.cpp

OBJS = $(SRCS:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)
OBJS3 = $(SRCS3:.cpp=.o)
OBJS_DIR = obj/

FLAGS = -Wall -Werror -Wextra -std=c++11

all: $(NAME) $(NAME2) $(NAME3) 

$(NAME): $(OBJS)
	$(CXX) -o $@ $^

$(NAME2): $(OBJS2)
	$(CXX) -o $@ $^

$(NAME3): $(OBJS3)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS) $(OBJS2) $(OBJS3)

fclean: clean
	rm -f $(NAME) $(NAME2) $(NAME3)

re: fclean all

del: fclean
	rm -rf Grace_kid.cpp
	rm -rf Sully_*

test: re
	./Colleen > out ; /bin/cat Colleen.cpp > in ; diff in out
	@/bin/rm in out

	./Grace ; diff Grace.cpp Grace_kid.cpp
	@/bin/rm -f Grace_kid.cpp

	mkdir -p tmp ; cp $(NAME3) tmp/ ; cd tmp ; ./$(NAME3); ls -la | grep $(NAME3) | wc -l; diff ../$(NAME3).cpp $(NAME3)_5.cpp; diff ../$(NAME3).cpp $(NAME3)_0.cpp; diff $(NAME3)_3.cpp $(NAME3)_2.cpp; cd ..
	@/bin/rm -rf tmp
