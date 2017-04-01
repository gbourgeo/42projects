#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 18:41:05 by gbourgeo          #+#    #+#              #
#    Updated: 2016/06/21 04:52:05 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isalnum.c \
	ft_isdigit.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memmove.c \
	ft_memcmp.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
	ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c\
	ft_lstaddend.c ft_lstswap.c \
	ft_tabdup.c ft_tablen.c ft_puttab.c ft_puttab_fd.c ft_tabdel.c \
	get_next_line.c \
	ft_split.c ft_split_whitespaces.c ft_str2join.c ft_strcdup.c \
	ft_strcharset.c ft_stricpy.c ft_strndup.c ft_strrcdup.c

OBJ_DIR = obj/

OBJ	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

WWW	= -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@echo Generating my libft...
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo CREATED: $(NAME)

$(OBJ_DIR)%.o: %.c
	@gcc $(WWW) -o $@ -c $< -I includes/

clean:
	@if test -d $(OBJ_DIR) ; then rm -rf $(OBJ_DIR) ; echo Erased: LIBFT - Objects. ; fi

fclean: clean
	@if test -f $(NAME) ; then rm -f $(NAME) ; echo Erased: $(NAME) ; fi

re: fclean all
