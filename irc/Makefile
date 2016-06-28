#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2016/06/26 18:48:42 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CLIENT	= client

CL_DIR	= src/client/

CL_SRC	= cl_main.c cl_getaddrinfo.c cl_loop.c cl_read_write.c cl_commands.c \
		cl_error.c

CL_OBJ	= $(CL_SRC:.c=.o)

SERVEUR	= serveur

SV_DIR	= src/serveur/

SV_SRC	= sv_accept.c sv_chan.c sv_cl_end.c sv_cl_read.c sv_cl_write.c \
		sv_command_client.c sv_error.c sv_getaddrinfo.c sv_join.c \
		sv_leave.c sv_loop.c sv_main.c sv_msg.c sv_send.c sv_split.c \
		sv_strchr.c

SV_OBJ	= $(SV_SRC:.c=.o)

COM_DIR	= src/common/

COM_SRC	= ft_free.c

COM_OBJ	= $(COM_SRC:.c=.o)

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
	$(WWW) -o $@ $^ -L $(LIBFT) -lft -lncurses
	@echo CREATED: $@

$(SERVEUR): $(OBJ_SV) $(OBJ_COM) | lib
	@$(WWW) -o $@ $^ -L $(LIBFT) -lft
	@echo CREATED: $@

$(OBJ_DIR)%.o: $(CL_DIR)%.c $(CL_DIR)cl_main.h $(COM_DIR)common.h | $(OBJ_DIR)
	$(WWW) -c $< -o $@ -I $(LIBFT_H) -I $(COM_DIR)

$(OBJ_DIR)%.o: $(SV_DIR)%.c $(SV_DIR)sv_main.h $(COM_DIR)common.h | $(OBJ_DIR)
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
