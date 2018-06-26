#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/16 18:53:45 by gbourgeo          #+#    #+#              #
#    Updated: 2018/06/25 22:27:41 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Colleen
NAME2 = Grace
NAME3 = Sully

SRCS = Colleen.c
SRCS2 = Grace.c
SRCS3 = Sully.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS2 = $(addprefix $(OBJS_DIR), $(SRCS2:.c=.o))
OBJS3 = $(addprefix $(OBJS_DIR), $(SRCS3:.c=.o))
OBJS_DIR = obj/

FLAGS = -Wall -Werror -Wextra

all: $(OBJS_DIR) $(NAME) $(NAME2) $(NAME3) 

$(OBJS_DIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $@ $^

$(NAME2): $(OBJS2)
	gcc $(FLAGS) -o $@ $^

$(NAME3): $(OBJS3)
	gcc $(FLAGS) -o $@ $^

$(OBJS_DIR)%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS_DIR)

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

	mkdir -p sullly ; cd sullly ; ../Sully; ls -la | wc -l; diff ../Sully.c Sully_0.c; diff Sully_3.c Sully_2.c; cd ..
	@/bin/rm -rf sullly
