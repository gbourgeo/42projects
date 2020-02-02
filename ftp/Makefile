# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2020/02/02 02:28:17 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT	= client
CLI_D	= src/client.d/
CLI_C	= cl_main.c						\
		cl_client_commands.c			\
		cl_client_end.c					\
		cl_client_loop.c				\
		cl_client_read.c				\
		cl_client_signals.c				\
		cl_commands.c					\
		cl_get_addrinfo.c				\
		cl_ncurses.c					\
		cl_ncurses_box.c				\
		cl_ncurses_write.c				\
		cl_params_get.c					\
		cl_params.c						\
		cl_params_1.c					\
		cl_server_recv.c				\
		cl_server_send.c				\
		cl_server_write.c				\

CLI_C_D = $(CLI_D)commands.d/
CLI_C += cl_cd.c						\
		cl_get.c						\
		cl_help.c						\
		cl_ls.c							\
		cl_mkd.c						\
		cl_put.c						\
		cl_pwd.c						\
		cl_quit.c						\
		cl_rm.c							\

SERVEUR	= server
SER_D	= src/server.d/
SER_C	= sv_main.c						\
		sv_assign_ptr.c					\
		sv_check_pid.c					\
		sv_commands.c					\
		sv_get_addr.c					\
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
		sv_client_init.c				\
		sv_client_recv.c				\
		sv_client_send.c				\
		sv_client_write.c				\
		sv_client_end.c					\
		sv_client_timeout.c				\
		sv_errors.c						\
		sv_free.c						\
		sv_validnumber.c				\
		sv_validpathname.c				\
		sv_response.c					\
		sv_response_opt.c				\

SER_C_D	= $(SER_D)commands.d/
SER_C	+= sv_cdup.c					\
		sv_change_working_directory.c	\
		sv_check_path.c					\
		sv_connect_to.c					\
		sv_cwd.c						\
		sv_dele.c						\
		sv_hdr.c						\
		sv_help_print.c					\
		sv_help.c						\
		sv_listen_from.c				\
		sv_mkd.c						\
		sv_new_pid.c					\
		sv_nlst.c						\
		sv_pass.c						\
		sv_pasv_listen.c				\
		sv_pasv.c						\
		sv_port.c						\
		sv_pwd.c						\
		sv_quit.c						\
		sv_recreate_path.c				\
		sv_regt.c						\
		sv_rein.c						\
		sv_retr.c						\
		sv_rmd.c						\
		sv_rmd_open.c					\
		sv_stor.c						\
		sv_stou.c						\
		sv_type.c						\
		sv_type_hdlr.c					\
		sv_user.c						\
		sv_welcome.c					\

COM_D	= src/common.d/
COM_C	= ft_init.c						\
		ft_check_option.c				\
		ft_close.c						\
		ft_error.c						\
		ft_get_command.c				\
		ft_getenv.c						\
		ft_ringbuffcpy.c				\
		ft_strsplit2.c					\
		ft_strcset.c					\
		ftp_strcmp.c					\
		signal_info.c					\

OBJ_D	= obj/
OBJ_C	= $(addprefix $(OBJ_D), $(CLI_C:.c=.o))
OBJ_S	= $(addprefix $(OBJ_D), $(SER_C:.c=.o))
OBJ_X	= $(addprefix $(OBJ_D), $(COM_C:.c=.o))

LIB_DIR	= libft/

HDRS	= -I includes/ -I $(LIB_DIR)includes/
LIBS	= -L $(LIB_DIR) -lft

CC		= /usr/bin/gcc
CFLAGS	= -Wall -Werror -Wextra
CFLAGS	+= -std=c11 -Wmissing-prototypes -pedantic -pedantic-errors -g3

ifeq ($(LEAKS),1)
$(echo "Sanitizing")
CFLAGS	+= -fsanitize=address -fsanitize=undefined
LIBS	+= -fsanitize=address -fsanitize=undefined
endif

all: $(OBJ_D) $(CLIENT) $(SERVEUR)

$(OBJ_D):
	mkdir -p $@

$(CLIENT): $(OBJ_X) $(OBJ_C)
	@make -sC $(LIB_DIR)
	@$(CC) -o $@ $^ $(LIBS) -ltermcap -lncurses
	@echo "GENERATED: $(CLIENT)"

$(SERVEUR): $(OBJ_X) $(OBJ_S)
	@make -sC $(LIB_DIR)
	@$(CC) -o $@ $^ $(LIBS)
	@echo "GENERATED: $(SERVEUR)"

$(OBJ_C): includes/cl_main.h includes/common.h

$(OBJ_S): includes/sv_main.h includes/common.h includes/sv_struct.h

$(OBJ_D)%.o: $(CLI_D)%.c
	@echo "Compile: $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(CLI_C_D)%.c
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

clean:
	@make -sC $(LIB_DIR) clean
	@rm -rf $(OBJ_D)

fclean: clean
	@make -sC $(LIB_DIR) fclean
	@rm -f $(CLIENT)
	@rm -f $(SERVEUR)

re: fclean all
