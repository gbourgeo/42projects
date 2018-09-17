#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2018/09/17 15:56:44 by root             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CLIENT	= client
CL_HDR	= inc/client/
CL_H	= cl_main.h
CL_DIR	= src/client/
CL_SRC	= cl_main.c cl_getaddrinfo.c cl_read_write.c cl_commands.c 				\
		cl_commands_next.c cl_error.c cl_send.c

SERVEUR	= server
SV_HDR	= inc/server/
SV_H	= sv_main.h conf.h
SV_DIR	= src/server/
SV_SRC	= get_conf_file.c is_chan_member.c sv_accept.c sv_allowed.c sv_away.c 		\
		sv_chan.c sv_channel_mode.c sv_chan_user_mode.c sv_cl_read.c sv_cl_write.c 	\
		sv_clear_client.c sv_check_clients.c sv_connect.c sv_err.c sv_error.c 		\
		sv_find.c sv_globcmp.c sv_help.c sv_init_server.c sv_join.c					\
		sv_join_channel.c sv_leave.c sv_leave_check.c sv_list.c sv_loop.c 			\
		sv_main.c sv_mode.c sv_motd.c sv_msg.c sv_msg_chan.c sv_new_client.c 		\
		sv_nick.c sv_nick_change.c sv_notice.c sv_oper.c sv_pass.c sv_quit.c	 	\
		sv_rpl.c sv_sendtochan.c sv_signals.c sv_split.c sv_strchr.c sv_tabcmp.c	\
		sv_topic.c sv_user.c sv_user_mode.c sv_welcome.c sv_who.c sv_who_info.c

COM_HDR = inc/common/
COM_H 	= common.h err_list.h help.h commands.h flags.h
COM_DIR	= src/common/
COM_SRC	= ft_free.c ft_strtoupper.c ft_strtolower.c sv_strcmp.c sv_strncmp.c 	\
		ft_strisalnum.c sv_strsplit.c

OBJ_DIR	= obj/
OBJ_CL	= $(addprefix $(OBJ_DIR), $(CL_SRC:.c=.o))
OBJ_SV	= $(addprefix $(OBJ_DIR), $(SV_SRC:.c=.o))
OBJ_COM	= $(addprefix $(OBJ_DIR), $(COM_SRC:.c=.o))

LIB_DIR	= libft/
LIB_HDR	= $(LIB_DIR)includes/

WWW		= gcc -Wall -Werror -Wextra

all: lib $(OBJ_DIR) $(CLIENT) $(SERVEUR)

lib:
	@make -C $(LIB_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(CLIENT): $(OBJ_CL) $(OBJ_COM)
	@make -C $(LIB_DIR)
	@$(WWW) -o $@ $^ -L $(LIB_DIR) -lft
	@echo CREATED: $@

$(SERVEUR): $(OBJ_SV) $(OBJ_COM)
	@make -C $(LIB_DIR)
	@$(WWW) -o $@ $^ -L $(LIB_DIR) -lft
	@echo CREATED: $@

$(OBJ_CL): $(addprefix $(CL_HDR), $(CL_H)) $(addprefix $(COM_HDR), $(COM_H))
$(OBJ_SV): $(addprefix $(SV_HDR), $(SV_H)) $(addprefix $(COM_HDR), $(COM_H))
$(OBJ_COM): $(addprefix $(COM_HDR), $(COM_H))

$(OBJ_DIR)%.o: $(CL_DIR)%.c | $(OBJ_DIR)
	@echo Compiling $<
	@$(WWW) -c $< -o $@ -I$(LIB_HDR) -I$(CL_HDR) -I$(COM_HDR)

$(OBJ_DIR)%.o: $(SV_DIR)%.c | $(OBJ_DIR)
	@echo Compiling $<
	@$(WWW) -c $< -o $@ -I$(LIB_HDR) -I$(SV_HDR) -I$(COM_HDR)

$(OBJ_DIR)%.o: $(COM_DIR)%.c | $(OBJ_DIR)
	@echo Compiling $<
	@$(WWW) -c $< -o $@ -I$(LIB_HDR) -I$(COM_HDR)

clean:
	@make -C $(LIB_DIR) clean
	@if [ -d $(OBJ_DIR) ]; then rm -r $(OBJ_DIR); echo "Erased: IRC - Objects."; fi

fclean: clean
	@make -C $(LIB_DIR) fclean
	@if [ -f $(CLIENT) ]; then rm -f $(CLIENT); echo Erased: $(CLIENT); fi
	@if [ -f $(SERVEUR) ]; then rm -f $(SERVEUR); echo Erased: $(SERVEUR); fi

re: fclean all
