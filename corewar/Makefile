# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/11/02 21:19:25 by dbaffier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM		= vm.d/
ASM		= asm.d/

all: vm vasm

vm:
	make -C $(VM)

vasm:
	make -C $(ASM)

clean:
	make -C $(VM) clean
	make -C $(ASM) clean

fclean: clean
	make -C $(VM) fclean
	make -C $(ASM) fclean

re: fclean all
