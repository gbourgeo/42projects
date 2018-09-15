# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beborch <beborch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 07:18:09 by beborch           #+#    #+#              #
#    Updated: 2018/08/29 04:39:05 by beborch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isprint.c ft_memset.c ft_putstr.c ft_strdup.c ft_strlen.c \
	   ft_tolower.c ft_toupper.c ft_atoi.c ft_bzero.c ft_memcpy.c \
	   ft_memccpy.c ft_memchr.c ft_memcmp.c ft_strcpy.c ft_strncpy.c \
	   ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c ft_strcmp.c \
	   ft_strncmp.c ft_strstr.c ft_putchar.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr_fd.c \
	   ft_putendl.c ft_putendl_fd.c ft_strnstr.c ft_isalpha.c ft_striter.c \
	   ft_striteri.c ft_strclr.c ft_memalloc.c ft_isalpha.c ft_isdigit.c \
	   ft_isascii.c ft_isalnum.c ft_isprint.c ft_strnew.c ft_strdel.c \
	   ft_strtrim.c ft_memdel.c ft_memmove.c ft_strequ.c ft_strjoin.c \
	   ft_strmap.c ft_strmapi.c ft_strnequ.c ft_strsplit.c ft_strsub.c \
	   ft_itoa.c ft_bn.c ft_putbin.c ft_strlcat.c ft_itb.c ft_strtb.c \
	   ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	   ft_lstmap.c

OBJ = $(SRC:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ) Makefile
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -Wall -Werror -Wextra -o $@ -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
