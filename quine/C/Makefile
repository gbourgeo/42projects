#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/16 18:53:45 by gbourgeo          #+#    #+#              #
#    Updated: 2017/12/17 01:53:00 by gbourgeo         ###   ########.fr        #
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

del:
	rm -rf Grace_kid.c
	rm -rf Sully_*
