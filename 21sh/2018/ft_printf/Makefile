# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 18:41:05 by gbourgeo          #+#    #+#              #
#    Updated: 2019/01/29 13:38:49 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprintf.a

SRC_DIR = src/
LIBFT_SRC = ft_pow.c
PRINTF_SRC = ft_printf.c ft_printf_write.c
PRINTF_BASE = ft_atouc.c ft_strtoupper.c pf_c.c	pf_x.c							\
		pf_di.c pf_o.c pf_p.c pf_percent.c pf_s.c pf_u.c pf_wchar.c pf_writes.c	\
		pf_routine.c pf_itoa_base.c
FPRINTF_SRC = ft_fprintf.c ft_fprintf_write.c
DPRINTF_SRC = ft_dprintf.c ft_dprintf_write.c
SPRINTF_SRC = ft_sprintf.c ft_sprintf_write.c
SNPRINTF_SRC = ft_snprintf.c ft_snprintf_write.c

OBJ_DIR = objs/
OBJ_PRINTF := $(addprefix $(OBJ_DIR), $(LIBFT_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(PRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(PRINTF_BASE:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(FPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(DPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(SPRINTF_SRC:.c=.o))
OBJ_PRINTF += $(addprefix $(OBJ_DIR), $(SNPRINTF_SRC:.c=.o))

WWW	= gcc -Wall -Werror -Wextra

INCLUDES = -I include/ -I ../libft/include/

OK = "ᚕ"

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ_PRINTF)
	@echo ""
	@ar rsc $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(OK) | tr -d '\n'
	@$(WWW) -o $@ -c $< $(INCLUDES)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
