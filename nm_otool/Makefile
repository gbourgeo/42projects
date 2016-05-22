#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/18 03:39:20 by gbourgeo          #+#    #+#              #
#    Updated: 2016/05/21 23:48:27 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_nm

SRC_DIR = nm/

SRC = ft_archive.c \
		ft_check_arc.c \
		ft_display.c \
		ft_do_nm.c \
		ft_error.c \
		ft_free.c \
		ft_init.c \
		ft_magic.c \
		ft_nm.c \
		ft_remove.c \
		ft_sections.c \
		ft_sort.c \
		ft_sort_stabs.c \
		ft_swap.c \
		ft_symb.c \
		ft_swap_bytes.c \
		ft_types.c

NAME_2 = ft_otool

SRC_DIR_2 = otool/

SRC_2 = ft_aff.c \
		ft_aff_arch.c \
		ft_archive.c \
		ft_check_arc.c \
		ft_fat.c \
		ft_free.c \
		ft_init.c \
		ft_openfile.c \
		ft_otool.c \
		ft_print_ar_hdr.c \
		ft_print_mach_header.c \
		ft_print_shared_libraries.c \
		ft_print_text_section.c \
		ft_print_data_section.c \
		ft_puthex.c \
		ft_swap_bytes.c \
		ft_power.c \
		ft_treat_file.c

OBJ_DIR = obj_nm/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_DIR_2 = obj_otool/

OBJ_2 = $(addprefix $(OBJ_DIR_2), $(SRC_2:.c=.o))

FLAGS = gcc -Wall -Werror -Wextra

LIBFT = libft

LIBFT_H = -I $(LIBFT)/includes/

all: lib $(NAME) $(NAME_2)

lib:
	@make -C $(LIBFT)
	@if ! test -d $(OBJ_DIR) ; then mkdir -p $(OBJ_DIR) ; echo mkdir -p $(OBJ_DIR) ; fi
	@if ! test -d $(OBJ_DIR_2) ; then mkdir -p $(OBJ_DIR_2) ; echo mkdir -p $(OBJ_DIR_2) ; fi

.PHONY: clean fclean re all

$(NAME): $(OBJ)
		$(FLAGS) -o $@ $^ -L $(LIBFT) -lft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		$(FLAGS) -o $@ -c $< $(LIBFT_H)

$(NAME_2): $(OBJ_2)
		$(FLAGS) -o $@ $^ -L $(LIBFT) -lft

$(OBJ_DIR_2)%.o: $(SRC_DIR_2)%.c
		$(FLAGS) -o $@ -c $< $(LIBFT_H)

clean:
		make -C $(LIBFT) clean
		@if test -d $(OBJ_DIR) ; then rm -r $(OBJ_DIR) ; echo rm -r $(OBJ_DIR) ; fi
		@if test -d $(OBJ_DIR_2) ; then rm -r $(OBJ_DIR_2) ; echo rm -r $(OBJ_DIR_2) ; fi

fclean: clean
		rm -f $(LIBFT)/libft.a
		@if test -f $(NAME) ; then rm -f $(NAME) ; echo rm -f $(NAME) ; fi
		@if test -f $(NAME_2) ; then rm -f $(NAME_2) ; echo rm -f $(NAME_2) ; fi

re: fclean all
