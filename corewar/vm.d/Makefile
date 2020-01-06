# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/10/25 02:57:49 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../corewar

VM_DIR		= ./
VM_SRC_D	= $(VM_DIR)srcs/
VM_INC_D	= $(VM_DIR)incs/
VM_SRC		+=	main.c					\
				arena_operations.c		\
				dump_map.c				\
				errors.c				\
				free.c					\
				game_instructions.c		\
				game_launch.c			\
				game_play.c				\
				get_arena.c				\
				get_args.c				\
				get_colors.c			\
				get_pauses.c			\
				get_player.c			\
				move_process_pc.c		\
				ncurses_aff_update.c	\
				ncurses_aff_update2.c	\
				ncurses_aff.c			\
				ncurses_create.c		\
				ncurses_init_end.c		\
				ncurses_wgetch.c		\
				op.c					\
				proc_functions.c		\
				signals.c				\
				swap_bytes.c			\
				operation_tools.c		\
				operations1_5.c			\
				operations6_10.c		\
				operations11_15.c		\
				operations16.c			\

OBJS_DIR	= $(VM_DIR)objs/
OBJS_VM		+= $(addprefix $(OBJS_DIR), $(VM_SRC:.c=.o))

DEP_DIR		= .deps/
DEP			= $(addprefix $(DEP_DIR), $(VM_SRC:.c=.d))

LFT_DIR		= ../libft/

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
CFLAGS		+= -std=c11 -Wmissing-prototypes -pedantic -pedantic-errors -g3
ifeq ($(SAN),"1")
CFLAGS		+= -fsanitize=address
endif

INCS		= -I$(LFT_DIR)inc -I$(VM_INC_D) -I/Users/naminei/.brew/opt/ncurses/include
LIBS		= -L$(LFT_DIR) -lft -lncurses
ifeq ($(SAN),"1")
LIBS		+= -fsanitize=address
endif

RED			= \x1b[1;31m
GREEN		= \x1b[1;32m
RESET		= \x1b[0m

all: $(DEP_DIR) $(OBJS_DIR) $(NAME)

$(DEP_DIR):
	@mkdir -p $@

$(OBJS_DIR):
	@mkdir -p $@

$(NAME): $(OBJS_VM)
	make -C $(LFT_DIR)
	$(CC) -o $@ $^ $(LIBS)

$(OBJS_DIR)%.o: $(VM_SRC_D)%.c
$(OBJS_DIR)%.o: $(VM_SRC_D)%.c $(DEP_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEP_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEP_DIR)$*.Td $(DEP_DIR)$*.d && touch $@

$(DEP_DIR)%.d: ;
.PRECIOUS: $@

-include $(DEP)

clean:
	$(RM) -rf $(OBJS_DIR)
	$(RM) -rf $(DEP_DIR)
	make -C $(LFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re
