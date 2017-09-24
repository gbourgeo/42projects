# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/09/18 04:57:47 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NMAP	=	ft_nmap

NAME		=   ft_nmap
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc -ggdb -lpthread -lpcap
FLAGS_O		=

SRCDIR_NMAP		=	srcs/
OBJDIR_NMAP		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_NMAP	=	\
					nmap.c				\
					flags.c				\
					initializer.c		\
					hosts.c				\
					ports.c				\
					get_next_line.c		\
					scan_type.c			\
					free.c				\
					threads.c			\
					scan.c				\
					tcp.c				\
					udp.c				\
					ip_header.c			\
					checksum.c			\
					socket.c			\
					interface.c			\
					tcp_flags.c			\
					thread_handler.c	\
					id.c				\
					queue.c				\
					pcap.c				\
					display.c			\
					os_scan.c			\
					service.c

INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_NMAP			=	$(addprefix $(SRCDIR_NMAP), $(SRCBASE_NMAP))
OBJS_NMAP			=	$(addprefix $(OBJDIR_NMAP), $(SRCBASE_NMAP:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_NMAP) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make re -C libft/ &&														\
		make NMAP && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_NMAP):
	mkdir -p $(OBJDIR_NMAP)
	mkdir -p $(dir $(OBJS_NMAP))

$(OBJDIR_NMAP)%.o : $(SRCDIR_NMAP)%.c | $(OBJDIR_NMAP)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

NMAP: $(OBJDIR_NMAP) $(OBJS_NMAP)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_NMAP) $(OBJS_NMAP) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_NMAP)"

clean:
	@rm -rf $(OBJDIR_NMAP)
	echo "\r\033[38;5;124m📕  CLEAN $(OBJDIR_NMAP)\033[0m\033[K";

fclean:		clean
	@rm -rf $(NAME_NMAP)
	echo "\r\033[38;5;124m📕  FCLEAN $(NAME_NMAP)\033[0m\033[K";

-include $(OBJS:.o=.d)
