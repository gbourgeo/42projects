#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2017/04/05 01:17:38 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CLIENT	= client

CL_DIR	= src/client/

CL_SRC	= cl_main.c cl_getaddrinfo.c cl_read_write.c cl_commands.c \
		cl_commands_next.c cl_error.c cl_send.c

CL_OBJ	= $(CL_SRC:.c=.o)

SERVEUR	= serveur

SV_DIR	= src/serveur/

SV_SRC	= get_users_list.c	\
		is_chan_member.c	\
		sv_accept.c 		\
		sv_away.c 			\
		sv_chan.c 			\
		sv_channel_mode.c 	\
		sv_chan_user_mode.c	\
		sv_cl_read.c 		\
		sv_cl_write.c 		\
		sv_clear_client.c 	\
		sv_check_clients.c	\
		sv_connect.c 		\
		sv_err.c 			\
		sv_error.c 			\
		sv_find.c			\
		sv_help.c 			\
		sv_init_server.c 	\
		sv_join.c 			\
		sv_join_channel.c	\
		sv_leave.c 			\
		sv_leave_check.c 	\
		sv_list.c 			\
		sv_loop.c 			\
		sv_main.c 			\
		sv_mode.c 			\
		sv_motd.c			\
		sv_msg.c			\
		sv_msg_chan.c		\
		sv_new_client.c 	\
		sv_nick.c 			\
		sv_nick_change.c 	\
		sv_notice.c 		\
		sv_pass.c			\
		sv_quit.c	 		\
		sv_rpl.c			\
		sv_sendtochan.c 	\
		sv_signals.c 		\
		sv_split.c 			\
		sv_strchr.c 		\
		sv_tabcmp.c			\
		sv_topic.c 			\
		sv_user.c 			\
		sv_user_mode.c		\
		sv_welcome.c 		\
		sv_who.c			\
		sv_who_info.c

SV_OBJ	= $(SV_SRC:.c=.o)

COM_DIR	= src/common/

COM_SRC	= ft_free.c ft_strtoupper.c ft_strtolower.c sv_strcmp.c sv_strncmp.c \
		ft_strisalnum.c

COM_OBJ	= $(COM_SRC:.c=.o)

COM_HDR = common.h err_list.h help.h commands.h flags.h

OBJ_DIR	= obj/

OBJ_CL	= $(addprefix $(OBJ_DIR), $(CL_OBJ))

OBJ_SV	= $(addprefix $(OBJ_DIR), $(SV_OBJ))

OBJ_COM	= $(addprefix $(OBJ_DIR), $(COM_OBJ))

LIBFT	= libft/

LIBFT_H	= $(LIBFT)includes/

WWW		= gcc -Wall -Werror -Wextra #-pedantic-errors -pedantic

.PHONY: all clean fclean re

all: lib $(OBJ_DIR) $(CLIENT) $(SERVEUR)

lib:
	@make -C $(LIBFT)

$(OBJ_DIR):
	@mkdir -p $@

$(CLIENT): $(OBJ_CL) $(OBJ_COM) | lib
	$(WWW) -o $@ $^ -L $(LIBFT) -lft
	@echo CREATED: $@

$(SERVEUR): $(OBJ_SV) $(OBJ_COM) | lib
	@$(WWW) -o $@ $^ -L $(LIBFT) -lft
	@echo CREATED: $@

$(OBJ_DIR)%.o: $(CL_DIR)%.c $(CL_DIR)cl_main.h $(addprefix $(COM_DIR), $(COM_HDR)) | $(OBJ_DIR)
	$(WWW) -c $< -o $@ -I $(LIBFT_H) -I $(COM_DIR)

$(OBJ_DIR)%.o: $(SV_DIR)%.c $(SV_DIR)sv_main.h $(addprefix $(COM_DIR), $(COM_HDR)) | $(OBJ_DIR)
	$(WWW) -c $< -o $@ -I $(LIBFT_H) -I $(COM_DIR)

$(OBJ_DIR)%.o: $(COM_DIR)%.c | $(OBJ_DIR)
	$(WWW) -c $< -o $@ -I $(LIBFT_H) -I $(COM_DIR)

clean:
	@make -C $(LIBFT) clean
	@if [ -d $(OBJ_DIR) ]; then rm -r $(OBJ_DIR); echo "Erased: IRC - Objects."; fi

fclean: clean
	@make -C $(LIBFT) fclean
	@if [ -f $(CLIENT) ]; then rm -f $(CLIENT); echo Erased: $(CLIENT); fi
	@if [ -f $(SERVEUR) ]; then rm -f $(SERVEUR); echo Erased: $(SERVEUR); fi

re: fclean all
