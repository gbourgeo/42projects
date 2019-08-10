# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/16 18:53:45 by gbourgeo          #+#    #+#              #
#    Updated: 2019/08/06 04:08:56 by gbourgeo         ###   ########.fr        #
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

	mkdir -p tmp ; cp $(NAME3) tmp/ ; cd tmp ; ./Sully; ls -la | grep $(NAME3) | wc -l; diff ../Sully.c Sully_5.c; diff ../Sully.c Sully_0.c; diff Sully_3.c Sully_2.c; cd ..
	@/bin/rm -rf tmp
