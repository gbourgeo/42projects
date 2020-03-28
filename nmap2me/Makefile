# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2020/03/28 15:44:13 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_nmap

SRCDIR_NMAP	= srcs/
OBJDIR_NMAP	= objs/
DEPDIR_NMAP	= .deps/
INCDIR_NMAP	= includes/

LIBFT_DIR	= libft/

SRCBASE_NMAP	= \
		main.c						\
		error.c						\
		free.c						\
		interface.c					\
		pcap.c						\
		socket.c					\
		threads.c					\
		init_hdr.c					\
		checksum.c					\
		id.c						\
#		packets_read.c				\
		packets_make.c				\
		ping_scan.c					\

SRCDIR_NMAP_OPT = $(SRCDIR_NMAP)options/
SRCBASE_NMAP_OPT	= \
		get_file_parameters.c		\
		get_ip_parameters.c			\
		get_new_addr.c				\
		get_options.c				\
		get_ports_parameters.c		\
		get_scans_parameters.c		\
		get_timeout_parameters.c	\
		get_threads_parameters.c	\
		get_help.c					\
		options.c					\

OBJS_NMAP	= $(addprefix $(OBJDIR_NMAP), $(SRCBASE_NMAP:.c=.o))
OBJS_NMAP	+= $(addprefix $(OBJDIR_NMAP), $(SRCBASE_NMAP_OPT:.c=.o))

DEPS_NMAP	= $(addprefix $(DEPDIR_NMAP), $(SRCBASE_NMAP:.c=.d))
DEPS_NMAP	+= $(addprefix $(DEPDIR_NMAP), $(SRCBASE_NMAP_OPT:.c=.d))

CC			= gcc
FLAGS		= -Wall -Werror -Wextra
INCS		= -I $(LIBFT_DIR)$(INCDIR_NMAP) -I $(INCDIR_NMAP)
LIBS		= -ggdb -lpthread -lpcap -L $(LIBFT_DIR) -lft

all: prepare $(NAME)

.PHONY: clean fclean re

prepare:
	@make -sC $(LIBFT_DIR)
	@mkdir -p $(OBJDIR_NMAP)
	@mkdir -p $(DEPDIR_NMAP)

$(NAME): $(OBJS_NMAP)
	$(CC) -o $@ $^ $(LIBS)

$(OBJDIR_NMAP)%.o: $(SRCDIR_NMAP)%.c
$(OBJDIR_NMAP)%.o: $(SRCDIR_NMAP)%.c $(DEPDIR_NMAP)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPDIR_NMAP)$*.Td $(FLAGS_ERR) -o $@ -c $< $(INCS)
	@mv -f $(DEPDIR_NMAP)$*.Td $(DEPDIR_NMAP)$*.d && touch $@

$(OBJDIR_NMAP)%.o: $(SRCDIR_NMAP_OPT)%.c
$(OBJDIR_NMAP)%.o: $(SRCDIR_NMAP_OPT)%.c $(DEPDIR_NMAP)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPDIR_NMAP)$*.Td $(FLAGS_ERR) -o $@ -c $< $(INCS)
	@mv -f $(DEPDIR_NMAP)$*.Td $(DEPDIR_NMAP)$*.d && touch $@

$(DEPDIR_NMAP)%.d: ;
.PRECIOUS: $@

-include $(DEPS_NMAP)

clean:
#	@make -C $(LIBFT_DIR) clean
	rm -rf $(DEPDIR_NMAP)
	rm -rf $(OBJDIR_NMAP)

fclean:		clean
#	@make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all
