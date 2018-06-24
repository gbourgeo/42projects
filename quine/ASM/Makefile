#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/24 00:41:04 by root              #+#    #+#              #
#    Updated: 2018/06/24 02:22:53 by root             ###   ########.fr        #
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

WWW = nasm
FLAGS = -f elf64

all: $(OBJS_DIR) $(NAME) $(NAME2) $(NAME3) 

$(OBJS_DIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	gcc -o $@ $^

$(NAME2): $(OBJS2)
	gcc -o $@ $^

$(NAME3): $(OBJS3)
	gcc -o $@ $^

$(OBJS_DIR)%.o: %.s
	$(WWW) $(FLAGS) -o $@ $<

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(NAME2) $(NAME3)

re: fclean del all

del:
	rm -rf Grace_kid.c
	rm -rf Sully_*
