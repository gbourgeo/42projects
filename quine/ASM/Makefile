# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/24 00:41:04 by root              #+#    #+#              #
#    Updated: 2019/08/11 04:34:00 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Colleen
NAME2 = Grace
NAME3 = Sully

SRCS = Colleen.s
SRCS2 = Grace.s
SRCS3 = Sully.s

OBJS = $(SRCS:.s=.o)
OBJS2 = $(SRCS2:.s=.o)
OBJS3 = $(SRCS3:.s=.o)

ASM = PATH=~/.brew/bin nasm
ARCH = -f macho64
FLAGS = -Wall -Werror -Wextra

all: $(NAME) $(NAME2) $(NAME3) 

$(NAME): $(OBJS)
	gcc -o $@ $^

$(NAME2): $(OBJS2)
	gcc -o $@ $^

$(NAME3): $(OBJS3)
	gcc -o $@ $^

$(OBJS_DIR)%.o: %.s
	$(ASM) $(ARCH) -o $@ $<

clean:
	rm -rf $(OBJS) $(OBJS2) $(OBJS3)

fclean: clean
	rm -f $(NAME) $(NAME2) $(NAME3)

re: fclean del all

del: fclean
	rm -rf Grace_kid.s
	rm -rf Sully_*

test: re
	./$(NAME) > out
	/bin/cat Colleen.s > in
	diff in out
	@/bin/rm in out

	./$(NAME2)
	diff Grace.s Grace_kid.s
	@/bin/rm Grace_kid.s

	mkdir -p tmp ; cp $(NAME3) tmp/ ; cd tmp ; ./$(NAME3); ls -la | grep $(NAME3) | wc -l; diff ../$(NAME3).s $(NAME3)_5.s; diff ../$(NAME3).s $(NAME3)_0.s; diff $(NAME3)_3.s $(NAME3)_2.s; cd ..
	@/bin/rm -rf tmp
