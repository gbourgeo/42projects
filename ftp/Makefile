# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2020/01/06 18:10:02 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT	= client
CLI_D	= src/client.d/
CLI_C	= cl_main.c						\
		cl_client_end.c					\
		cl_client_signals.c				\
		cl_get_addrinfo.c				\
		cl_ncurses.c					\
		cl_ncurses_box.c				\
		cl_params_get.c					\
		cl_params.c						\
		cl_params_1.c					\

SERVEUR	= server
SER_D	= src/server.d/
SER_C	= sv_main.c						\
		sv_check_pid.c					\
		sv_commands.c					\
		sv_data_accept.c				\
		sv_get_addr.c					\
		sv_open_port.c					\
		sv_params.c						\
		sv_params_1.c					\
		sv_params_2.c					\
		sv_params_get.c					\
		sv_user_file.c					\
		sv_user_get.c					\
		sv_user_new.c					\
		sv_user_parse.c					\
		sv_user_save.c					\
		sv_server_end.c					\
		sv_server_info.c				\
		sv_server_loop.c				\
		sv_server_accept.c				\
		sv_server_close.c				\
		sv_server_signals.c				\
		sv_client_recv.c				\
		sv_client_send.c				\
		sv_client_write.c				\
		sv_client_end.c					\
		sv_client_timeout.c				\
		sv_errors.c						\
		sv_free.c						\

SER_C_D	= $(SER_D)commands.d/
SER_C	+= sv_cd.c						\
		sv_change_working_directory.c	\
		sv_check_path.c					\
		sv_cmd_err.c					\
		sv_cmd_ok.c						\
		sv_get.c						\
		sv_help.c						\
		sv_ls.c							\
		sv_mkdir.c						\
		sv_put.c						\
		sv_pwd.c						\
		sv_quit.c						\
		sv_rmdir.c						\
		sv_hdr.c						\
		sv_recreate_path.c				\
		sv_register.c					\
		sv_sign.c						\
		sv_transfert.c					\
		sv_unlink.c						\

COM_D	= src/common.d/
COM_C	= ft_init.c						\
		ft_check_option.c				\
		ft_close.c						\
		ft_error.c						\
		ft_get_command.c				\
		ft_getenv.c						\
		ft_strsplit2.c					\
		ft_strcset.c					\
		signal_info.c					\

OBJ_D	= obj/
OBJ_C	= $(addprefix $(OBJ_D), $(CLI_C:.c=.o))
OBJ_S	= $(addprefix $(OBJ_D), $(SER_C:.c=.o))
OBJ_X	= $(addprefix $(OBJ_D), $(COM_C:.c=.o))

LIB_DIR	= libft/

HDRS	= -I includes/ -I $(LIB_DIR)includes/
LIBS	= -L $(LIB_DIR) -lft

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
CFLAGS	+= -std=c11 -Wmissing-prototypes -pedantic -pedantic-errors -g3

ifeq ($(LEAKS),)
CFLAGS	+= -fsanitize=address
LIBS	+= -fsanitize=address
endif

all: $(CLIENT) $(SERVEUR)

$(CLIENT): $(OBJ_X) $(OBJ_C)
	@make -C $(LIB_DIR)
	@$(CC) -o $@ $^ $(LIBS) -lncurses
	@echo "GENERATED: $(CLIENT)"

$(SERVEUR): $(OBJ_X) $(OBJ_S)
	@make -C $(LIB_DIR)
	@$(CC) -o $@ $^ $(LIBS)
	@echo "GENERATED: $(SERVEUR)"

$(OBJ_C): includes/cl_main.h includes/common.h

$(OBJ_S): includes/sv_main.h includes/common.h

$(OBJ_D)%.o: $(CLI_D)%.c
	@echo "Compile: $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(SER_D)%.c
	@echo "Compile: $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(SER_C_D)%.c
	@echo "Compile: $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(COM_D)%.c | $(OBJ_D)
	@echo "Compile: $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDRS)

$(OBJ_D):
	mkdir -p $@

clean:
	@make -C $(LIB_DIR) clean
	@if test -d $(OBJ_D); then rm -r $(OBJ_D) && echo rm -r $(OBJ_D) ; fi

fclean: clean
	@make -C $(LIB_DIR) fclean
	@if test -f $(CLIENT) ; then rm $(CLIENT) && echo rm $(CLIENT) ; fi
	@if test -f $(SERVEUR) ; then rm $(SERVEUR) && echo rm $(SERVEUR) ; fi

re: fclean all
