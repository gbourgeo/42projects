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

NAME			=   ft_nmap

SRCDIR_NMAP		=	./srcs/
OBJDIR_NMAP		=	./objs/
INCDIR			=	./includes/

LIBFT_DIR		=	./libft/

SRCBASE_NMAP	=	\
					nmap.c 				\
					get_parameters.c 	\
					error.c 			\
					interface.c 		\
					ping_scan.c 		\
					pcap.c 				\
					start.c 			

HDRBASE_NMAP	= 	\
					all.h

OBJS_NMAP		=	$(addprefix $(OBJDIR_NMAP), $(SRCBASE_NMAP:.c=.o))

CC				=	gcc
FLAGS 			=	-ggdb -lpthread -lpcap -L $(LIBFT_DIR) -lft
FLAGS_ERR		=	-Wall -Werror -Wextra

all: $(OBJDIR_NMAP) $(NAME)

.PHONY: clean fclean re

$(OBJDIR_NMAP):
	mkdir -p $(OBJDIR_NMAP)
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS_NMAP)
	$(CC) -o $@ $^ $(FLAGS)

$(OBJDIR_NMAP)%.o : $(SRCDIR_NMAP)%.c
	$(CC) $(FLAGS_ERR) -c $< -o $@ -I $(LIBFT_DIR)$(INCDIR) -I $(INCDIR)

clean:
#	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR_NMAP)

fclean:		clean
#	@make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

ff: fclean
	make -C $(LIBFT_DIR) fclean
