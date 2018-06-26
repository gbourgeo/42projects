#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/24 00:41:04 by root              #+#    #+#              #
#    Updated: 2018/06/27 01:11:36 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Colleen
NAME2 = Grace
NAME3 = Sully

SRCS = Colleen.s
SRCS2 = Grace.s
SRCS3 = Sully.s

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.s=.o))
OBJS2 = $(addprefix $(OBJS_DIR), $(SRCS2:.s=.o))
OBJS3 = $(addprefix $(OBJS_DIR), $(SRCS3:.s=.o))
OBJS_DIR = obj/

ASM = ~/Downloads/nasm-2.11.02/nasm
ARCH = -f macho64
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

$(OBJS_DIR)%.o: %.s
	$(ASM) $(ARCH) -o $@ $<

clean:
	rm -rf $(OBJS_DIR)

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

	mkdir -p sullly ; cd sullly; ../$(NAME3); ls -la | wc -l; diff ../Sully.s Sully_0.s; diff Sully_3.s Sully_2.s; cd ..
	@/bin/rm -rf sullly
