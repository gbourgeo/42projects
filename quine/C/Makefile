# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/16 18:53:45 by gbourgeo          #+#    #+#              #
#    Updated: 2019/08/15 01:53:11 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Colleen
NAME2 = Grace
NAME3 = Sully

SRCS = Colleen.c
SRCS2 = Grace.c
SRCS3 = Sully.c

OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS2:.c=.o)
OBJS3 = $(SRCS3:.c=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME) $(NAME2) $(NAME3) 

$(NAME): $(OBJS)
	gcc -o $@ $^

$(NAME2): $(OBJS2)
	gcc -o $@ $^

$(NAME3): $(OBJS3)
	gcc -o $@ $^

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(OBJS2) $(OBJS3)

fclean: clean
	rm -f $(NAME) $(NAME2) $(NAME3)

re: fclean del all

del: fclean
	rm -rf Grace_kid.c
	rm -rf Sully_*

test: re
	./Colleen > out ; /bin/cat Colleen.c > in ; diff in out
	@/bin/rm in out

	./Grace ; diff Grace.c Grace_kid.c
	@/bin/rm -f Grace_kid.c

	rm -rf tmp ; mkdir -p tmp ; cp $(NAME3) tmp/ ; cd tmp ; ./$(NAME3); ls -la | grep $(NAME3) | wc -l; diff ../$(NAME3).c $(NAME3)_5.c; diff ../$(NAME3).c $(NAME3)_0.c; diff $(NAME3)_3.c $(NAME3)_2.c; cd ..
	@/bin/rm -rf tmp
