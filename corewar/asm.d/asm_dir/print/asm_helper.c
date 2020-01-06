/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:50:13 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/03 17:55:32 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "ft_printf.h"

static void	asm_helper2(void)
{
	ft_printf("\tf path\t:  get the fisrt argument after ");
	ft_printf("flags as a directory for the future created file\n");
	ft_printf("\ts name\t:  get the fisrt argument after ");
	ft_printf("flags as the name of the future created file\n\n");
	ft_printf("    DEASM\n");
	ft_printf("\tThe flag `d` allow you to send in asm a .cor file, ");
	ft_printf("some flags are disable here.\n");
	ft_printf("\tFlags `s`, `f` are not allowed and `n` ");
	ft_printf("will have no action.\n\n");
	ft_printf("\td\t:  take a .cor file and create the equivalent ");
	ft_printf(".s file with the unique extension .d.s\n\n");
	ft_printf("EXAMPLE\n");
	ft_printf("\t./asm -n file.s\n\n");
	ft_printf("AUTHOR\n");
	ft_printf("\tdbaffier, gbourgeo, bmellon, mmonier, ");
	ft_printf("and all the lifesavers on Google (;\n\n");
	ft_printf("SEE ALSO\n");
	ft_printf("\t./vm\n");
}

void		asm_helper(void)
{
	ft_printf("NAME\n");
	ft_printf("\tasm, best version\n\n");
	ft_printf("SYNOPSIS\n");
	ft_printf("\tusage : asm [-Ponp] [-f path] [-s name] file.s ...\n\t\t");
	ft_printf("[-d] file.cor ...\n\n");
	ft_printf("DESCRIPTION\n");
	ft_printf("\tasm is a program compiling .s file to .cor in purpose ");
	ft_printf("to use it in a corewar arena.\n\n");
	ft_printf("\tP\t:  while `f` or `s` disable, ");
	ft_printf("print the path to the file created\n");
	ft_printf("\to\t:  if `n` enable, print hexdump offset ; ");
	ft_printf("if not print file rights and creation date\n");
	ft_printf("\tn\t:  launch an interactive visu while encoding\n");
	ft_printf("\tp\t:  while `f` or `s` disable, ");
	ft_printf("print the path to the file created with the file name\n\n");
	ft_printf("    MUTIPLE FILE DISABLE\n");
	ft_printf("\tFollowing flags will disable multiple file on asm, ");
	ft_printf("and they are incompatible together.\n");
	ft_printf("\tUsing `s` with `f` will return an error.\n");
	ft_printf("\tFlags `p` and `P` are disabled here ");
	ft_printf("so they will have no action.\n\n");
	asm_helper2();
	exit(0);
}
