# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 18:41:05 by gbourgeo          #+#    #+#              #
#    Updated: 2019/07/17 13:20:10 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = srcs/
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
	ft_strcharset.c ft_stricpy.c ft_strndup.c ft_strrcdup.c ft_freestr.c \
	ft_freetab.c ft_iswhitespace.c ft_split_whitespaces.c ft_pow.c

PRINTF_DIR = ft_printf/
PRINTF_SRC = ft_printf.c ft_printf_write.c
PRINTF_BASE = ft_atouc.c ft_itoa_base.c ft_strtoupper.c pf_c.c	pf_x.c	\
		pf_di.c pf_o.c pf_p.c pf_percent.c pf_s.c pf_u.c pf_wchar.c pf_writes.c	\
		pf_routine.c
FPRINTF_SRC = ft_fprintf.c ft_fprintf_write.c
DPRINTF_SRC = ft_dprintf.c ft_dprintf_write.c
SPRINTF_SRC = ft_sprintf.c ft_sprintf_write.c
SNPRINTF_SRC = ft_snprintf.c ft_snprintf_write.c
VPRINTF_SRC = ft_vprintf.c ft_vprintf_write.c

OBJ_DIR = obj/
OBJ_SRC	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_PRINTF = $(addprefix $(OBJ_DIR), $(PRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(PRINTF_BASE:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(FPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(DPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(SPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(SNPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(VPRINTF_SRC:.c=.o))

WWW	= gcc -Wall -Werror -Wextra

INCLUDES = -I includes/

all: premade $(NAME)

premade:
	@if !(test -f $(NAME)) ; then echo -n "Generating $(NAME) "; fi
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_SRC) $(OBJ_PRINTF)
	@ar rc $@ $^
	@ranlib $@
	@echo " Done!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo -n .
	@$(WWW) -o $@ -c $< $(INCLUDES)

$(OBJ_DIR)%.o: $(PRINTF_DIR)%.c
	@echo -n .
	@$(WWW) -o $@ -c $< $(INCLUDES)

clean:
	@if test -d $(OBJ_DIR) ; then rm -rf $(OBJ_DIR) ; echo Libft .o erased. ; fi

fclean: clean
	@if test -f $(NAME) ; then rm -f $(NAME) ; echo libft $(NAME) erased. ; fi

re: fclean all

.PHONY: clean fclean re
