#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2018/08/29 12:06:24 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Durex
SRC		= main.c install.c durex.c server.c client.c encrypt.c commands.c
SRC		+= signal.c move.c reporter.c stdlib.c library.c shell.c
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEP		= $(addprefix $(DEP_DIR), $(SRC:.c=.d))
SRC_DIR	= srcs/
HDR_DIR = -I includes/
OBJ_DIR	= objs/
DEP_DIR = .deps/
LIB_DIR	= libft/
FLAGS	= -Wall -Werror -Wextra

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $(DEP_DIR)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEP_DIR)$*.Td $(FLAGS) -o $@ -c $< $(HDR_DIR)
	@mv -f $(DEP_DIR)$*.Td $(DEP_DIR)$*.d && touch $@

$(OBJ_DIR)shell.o: FLAGS += -D_XOPEN_SOURCE=600

$(DEP_DIR)%.d: ;
.PRECIOUS: $@

-include $(DEP)

clean:
	/bin/rm -rf $(OBJ_DIR)
	/bin/rm -rf $(DEP_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

rm:
	systemctl stop $(NAME)
	systemctl disable $(NAME)
	@if test -f /bin/Durex; then rm /bin/Durex && echo rm Durex; fi
	@if test -f /etc/init.d/Durex; then rm /etc/init.d/Durex && echo rm Durex init; fi
	@if test -f /lib/systemd/system/Durex.service; then rm /lib/systemd/system/Durex.service && echo rm Durex service; fi
	@if test -f /etc/systemd/Durex.conf; then rm /etc/systemd/Durex.conf && echo rm Durex conf; fi
	@if test -f /var/log/Durex.log; then rm /var/log/Durex.log && echo rm Durex log; fi
	@if test -f /var/lock/Durex.lock; then rm /var/lock/Durex.lock && echo rm Durex lock; fi

rt: rm all
	./$(NAME)

passwd:
	$(CC) -o pass other/passwd.c
hex:
	$(CC) -o hex other/txttohex.c
