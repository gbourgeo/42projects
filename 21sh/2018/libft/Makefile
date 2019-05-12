# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/27 19:43:45 by rfontain          #+#    #+#              #
#    Updated: 2018/11/22 05:58:43 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = libft.a

SRCS_D = src/
SRCS =	ft_memalloc.c		ft_putendl.c		ft_strcpy.c			\
		ft_strmapi.c		ft_strsub.c			ft_memccpy.c		\
		ft_putendl_fd.c		ft_strdel.c			ft_strncat.c		\
		ft_strtrim.c		ft_atoi.c			ft_memchr.c			\
		ft_putnbr.c			ft_strdup.c			ft_strncmp.c		\
		ft_tolower.c		ft_bzero.c			ft_memcmp.c			\
		ft_putnbr_fd.c		ft_strequ.c			ft_strncpy.c		\
		ft_toupper.c		ft_isalnum.c		ft_memcpy.c			\
		ft_putstr.c			ft_striter.c		ft_strnequ.c		\
		ft_isalpha.c		ft_memdel.c			ft_putstr_fd.c		\
		ft_striteri.c		ft_strnew.c			ft_isascii.c		\
		ft_memmove.c		ft_strcat.c			ft_strjoin.c		\
		ft_strnstr.c		ft_isdigit.c		ft_memset.c			\
		ft_strchr.c			ft_strlcat.c		ft_strrchr.c		\
		ft_isprint.c		ft_putchar.c		ft_strclr.c			\
		ft_strlen.c			ft_strsplit.c		ft_itoa.c			\
		ft_putchar_fd.c		ft_strcmp.c			ft_strmap.c			\
		ft_strstr.c			ft_lstadd.c			ft_lstiter.c		\
		ft_lstnew.c			ft_lstdelone.c		ft_lstdel.c			\
		ft_lstmap.c			ft_occuc.c			ft_strjoinfree.c	\
		ft_lstadd_back.c	ft_putstrstr.c		ft_putstrstr_fd.c	\
		ft_strrev.c			ft_copyuntil.c		ft_strjoinch.c		\
		ft_for.c			ft_strup.c			ft_strlow.c			\
		ft_itoa_base.c		get_next_line.c		ft_abs.c			\
		ft_putend.c			ft_putnbend.c		ft_putendnb.c		\
		ft_strsplit_ws.c	ft_find.c			ft_putstr_cl.c		\
		ft_putnbr_cl.c		ft_putendl_cl.c		ft_putend_cl.c		\
		ft_strlen_ch.c		ft_free.c			strdup_until.c		\
		strnjoin.c			stercat.c			ft_strnchr.c		\
		ft_strndup.c		ft_putchars.c		ft_isspace.c

INC = include/ 

OK = "ᚕ"

OBJS_D = objs/
OBJS = $(addprefix $(OBJS_D), $(SRCS:.c=.o))

all: $(OBJS_D) $(NAME)

$(OBJS_D):
	@mkdir -p $@

$(NAME): $(OBJS)
	@echo ""
	@ar rsc $(NAME) $(OBJS)

$(OBJS_D)%.o: $(SRCS_D)%.c
	@echo $(OK) | tr -d '\n'
	@$(CC) $(CFLAGS) -I $(INC) -o $@ -c $?

clean:
	@rm -rf $(OBJS_D)

fclean: clean
	@rm -f $(NAME)

re: fclean all
