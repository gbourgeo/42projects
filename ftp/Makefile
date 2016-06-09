#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/12 14:11:41 by gbourgeo          #+#    #+#              #
#    Updated: 2016/06/09 16:42:32 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CLIENT	= client

SERVEUR	= serveur

OBJ_DIR	= obj/

LIBFT	= libft/

SRC_C	= cl_main.c cl_loop.c cl_prompt.c cl_help.c cl_ls_and_pwd.c cl_get.c \
		cl_put.c cl_help.c cl_cd.c cl_commands.c cl_lcd.c cl_change_pwds.c \
		cl_end.c cl_mkdir_rmdir_unlink.c cl_mget_mput.c ft_signals.c \

SRC_S	= sv_main.c sv_loop.c sv_launch_client.c sv_ls.c sv_cd.c sv_get.c \
		sv_put.c sv_client_end.c sv_mkdir_rmdir_unlink.c \

SRC_X	= messages.c ft_error.c ft_free.c ft_aff_ip.c \
		ft_split_whitespaces.c ft_getenv.c ft_get_command.c \
		ft_get_path.c ft_strndup.c file_error.c ft_putendn.c

OBJ_C	= $(addprefix $(OBJ_DIR), $(SRC_C:.c=.o))
OBJ_S	= $(addprefix $(OBJ_DIR), $(SRC_S:.c=.o))
OBJ_X	= $(addprefix $(OBJ_DIR), $(SRC_X:.c=.o))

LIBFT_H	= -I $(LIBFT)includes/
LIBFT_A	= -L $(LIBFT) -lft

WWW		= gcc -Wall -Werror -Wextra

.PHONY: all lib clean fclean re

all: $(CLIENT) $(SERVEUR)

$(CLIENT): $(OBJ_X) $(OBJ_C)
	@make -C $(LIBFT)
	@$(WWW) -o $@ $^ $(LIBFT_H) $(LIBFT_A)
	@echo "GENERATED: $(CLIENT)"

$(SERVEUR): $(OBJ_X) $(OBJ_S)
	@make -C $(LIBFT)
	@$(WWW) -o $@ $^ $(LIBFT_H) $(LIBFT_A)
	@echo "GENERATED: $(SERVEUR)"

$(OBJ_C): cl_main.h common.h

$(OBJ_S): sv_main.h common.h

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compile: $<"
	@$(WWW) -o $@ -c $< $(LIBFT_H)

clean:
	@make -C libft clean
	@if test -d $(OBJ_DIR) ; then rm -r $(OBJ_DIR) ; echo rm -f $(OBJ_C) $(OBJ_S) ; fi

fclean: clean
	@make -C libft fclean
	@if test -f $(CLIENT) ; then rm -f $(CLIENT) ; echo rm -f $(CLIENT) ; fi
	@if test -f $(SERVEUR) ; then rm -f $(SERVEUR) ; echo rm -f $(SERVEUR) ; fi

re: fclean all
