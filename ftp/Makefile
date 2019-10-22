# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2019/10/22 02:02:20 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT	= client
CLI_D	= src/client/
CLI_C	= cl_main.c				\
		cl_loop.c				\
		cl_prompt.c				\
		cl_help.c				\
		cl_ls_and_pwd.c			\
		cl_get.c				\
		cl_put.c				\
		cl_help.c				\
		cl_cd.c					\
		cl_commands.c			\
		cl_lcd.c				\
		cl_change_pwds.c		\
		cl_end.c				\
		cl_mkdir_rmdir_unlink.c	\
		cl_mget_mput.c			\
		ft_signals.c			\

SERVEUR	= server
SER_D	= src/server/
SER_C	= sv_main.c				\
		sv_params.c				\
		sv_getaddr.c			\
		sv_aff_ip.c				\
		sv_loop.c				\
		sv_accept.c				\
		sv_client_recv.c		\
		sv_client_send.c		\
		sv_client_write.c		\
		sv_client_end.c			\
		sv_server_close.c		\
		sv_signals.c			\
		sv_free.c				\

SER_C_D	= $(SER_D)commands/
SER_C	+= sv_ls.c				\
		sv_cd.c					\
		sv_check_path.c			\
		# sv_get.c				\
		# sv_put.c				\
		# sv_mkdir_rmdir_unlink.c	\
		# sv_quit.c				\

COM_D	= src/common/
COM_C	= ft_init.c				\
		ft_error.c				\
		ft_freetab.c			\
		ft_split_whitespaces.c	\
		ft_getenv.c				\
		ft_get_command.c		\
		ft_get_path.c			\
		ft_strndup.c			\
		ft_putendn.c			\
#		file_error.c			\

OBJ_D	= obj/
OBJ_C	= $(addprefix $(OBJ_D), $(CLI_C:.c=.o))
OBJ_S	= $(addprefix $(OBJ_D), $(SER_C:.c=.o))
OBJ_X	= $(addprefix $(OBJ_D), $(COM_C:.c=.o))

LIB_DIR	= libft/

HDRS	= -I includes/ -I $(LIB_DIR)includes/
LIBS	= -L $(LIB_DIR) -lft

WWW		= gcc -Wall -Werror -Wextra

.SECONDEXPANSION:

all: $(CLIENT) $(SERVEUR)

$(CLIENT): $(OBJ_X) $(OBJ_C)
	@make -C $(LIB_DIR)
	@$(WWW) -o $@ $^ $(LIBS)
	@echo "GENERATED: $(CLIENT)"

$(SERVEUR): $(OBJ_X) $(OBJ_S)
	@make -C $(LIB_DIR)
	@$(WWW) -o $@ $^ $(LIBS)
	@echo "GENERATED: $(SERVEUR)"

$(OBJ_C): includes/cl_main.h includes/common.h

$(OBJ_S): includes/sv_main.h includes/common.h

$(OBJ_D)%.o: $(CLI_D)%.c
	@echo "Compile: $<"
	@$(WWW) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(SER_D)%.c
	@echo "Compile: $<"
	@$(WWW) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(SER_C_D)%.c
	@echo "Compile: $<"
	@$(WWW) -o $@ -c $< $(HDRS)

$(OBJ_D)%.o: $(COM_D)%.c | $(OBJ_D)
	@echo "Compile: $<"
	@$(WWW) -o $@ -c $< $(HDRS)

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
