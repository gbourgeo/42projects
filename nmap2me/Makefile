# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2020/04/30 12:04:11 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_nmap

SRCDIR_NMAP	= srcs/
OBJDIR_NMAP	= objs/
DEPDIR_NMAP	= .deps/
INCDIR_NMAP	= includes/

LIBFT_DIR	= libft/

SRCBASE_NMAP	= \
		checksum.c					\
		error.c						\
		find.c						\
		free.c						\
		init_hdr.c					\
		main.c						\
		pcap_init.c					\
		pcap_launch.c				\
		resolution.c				\
		report.c					\
		socket.c					\
		threads.c					\
		time.c						\

SRCDIR_NMAP_OPT = $(SRCDIR_NMAP)options/
SRCBASE_NMAP_OPT	= \
		add_new_addr.c				\
		del_new_addr.c				\
		get_debug_parameters.c		\
		get_file_parameters.c		\
		get_iflist_parameters.c		\
		get_interface_parameters.c	\
		get_ip_parameters.c			\
		get_options.c				\
		get_ports_parameters.c		\
		get_retry_parameters.c		\
		get_scans_parameters.c		\
		get_timeout_parameters.c	\
		get_threads_parameters.c	\
		get_verbose_parameters.c	\
		get_help.c					\
		options.c					\

OBJS_NMAP	= $(addprefix $(OBJDIR_NMAP), $(SRCBASE_NMAP:.c=.o))
OBJS_NMAP	+= $(addprefix $(OBJDIR_NMAP), $(SRCBASE_NMAP_OPT:.c=.o))

DEPS_NMAP	= $(addprefix $(DEPDIR_NMAP), $(SRCBASE_NMAP:.c=.d))
DEPS_NMAP	+= $(addprefix $(DEPDIR_NMAP), $(SRCBASE_NMAP_OPT:.c=.d))

CC			= gcc
FLAGS		= -Wall -Werror -Wextra
INCS		= -I $(LIBFT_DIR)$(INCDIR_NMAP) -I $(INCDIR_NMAP)
LIBS		= -lpthread -lpcap -L $(LIBFT_DIR) -lft

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
	$(CC) -MT $@ -MMD -MP -MF $(DEPDIR_NMAP)$*.Td $(FLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPDIR_NMAP)$*.Td $(DEPDIR_NMAP)$*.d && touch $@

$(OBJDIR_NMAP)%.o: $(SRCDIR_NMAP_OPT)%.c
$(OBJDIR_NMAP)%.o: $(SRCDIR_NMAP_OPT)%.c $(DEPDIR_NMAP)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPDIR_NMAP)$*.Td $(FLAGS) -o $@ -c $< $(INCS)
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
