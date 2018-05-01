/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 03:29:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/30 23:19:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

int main()
{

/*	ft_printf(">------------<%46.33zo>------------<\n", 0);
	printf(">------------<%46.33zo>------------<\n", 0);
	ft_printf("^.^/%44zo^.^/\n", 0);
	printf("^.^/%44zo^.^/\n", 0);
	ft_printf("^.^/%46.10zo^.^/\n", 0);
	printf("^.^/%46.10zo^.^/\n", 0);
	ft_printf(">------------<%8jo>------------<\n", 0);
	printf(">------------<%8jo>------------<\n", 0);
	ft_printf("^.^/%19.37jo^.^/\n", 0);
	printf("^.^/%19.37jo^.^/\n", 0);
	ft_printf(">------------<%16hho>------------<\n", 0);
	printf(">------------<%16hho>------------<\n", 0);
	ft_printf("!%42.58hho!\n", 0);
	printf("!%42.58hho!\n", 0);
	ft_printf("42%38ho42\n", 0);
	printf("42%38ho42\n", 0);
	ft_printf(">------------<%56.7zo>------------<\n", 0);
	printf(">------------<%56.7zo>------------<\n", 0);
	ft_printf("\\!/%3o\\!/\n", 0);
	printf("\\!/%3o\\!/\n", 0);
	ft_printf("!%25.20o!\n", 0);
	printf("!%25.20o!\n", 0);
	ft_printf("!%16.40o!\n", 0);
	printf("!%16.40o!\n", 0);
	ft_printf("!%o!\n", 0);
	printf("!%o!\n", 0);
	ft_printf("42%038.34zo42\n", 0);
	printf("42%038.34zo42\n", 0);
	ft_printf("!%#12zo!\n", 0);
	printf("!%#12zo!\n", 0);
	ft_printf("42%60.48zo42\n", 0);
	printf("42%60.48zo42\n", 0);
	ft_printf(">------------<%#16.2zo>------------<\n", 0);
	printf(">------------<%#16.2zo>------------<\n", 0);
	ft_printf("42%#14zo42\n", -1206452436);
	printf("42%#14zo42\n", -1206452436);
	ft_printf("!%-#36zo!\n", 0);
	printf("!%-#36zo!\n", 0);
	ft_printf("^.^/%#-.1zo^.^/\n", 0);
	printf("^.^/%#-.1zo^.^/\n", 0);
	ft_printf("^.^/%-40.4zo^.^/\n", 0);
	printf("^.^/%-40.4zo^.^/\n", 0);
	ft_printf("!%-44.40zo!\n", -963586792);
	printf("!%-44.40zo!\n", -963586792);
	ft_printf("^.^/%-54zo^.^/\n", 0);
	printf("^.^/%-54zo^.^/\n", 0);
	ft_printf("!%-#16.50zo!\n", 0);
	printf("!%-#16.50zo!\n", 0);
	ft_printf("42%-#1.2zo42\n", 0);
	printf("42%-#1.2zo42\n", 0);
	ft_printf("42%#-37.1zo42\n", 0);
	printf("42%#-37.1zo42\n", 0);
	ft_printf("!%-#32zo!\n", 0);
	printf("!%-#32zo!\n", 0);
	ft_printf("%-4.2zo\n", 0);
	printf("%-4.2zo\n", 0);
	ft_printf("42%-54.26zo42\n", 0);
	printf("42%-54.26zo42\n", 0);
	ft_printf("42%#2.1zo42\n", 0);
	printf("42%#2.1zo42\n", 0);

	printf("\n");
	ft_printf("\\!/%19.7zu\\!/\n", 0);
	printf("\\!/%19.7zu\\!/\n", 0);
	ft_printf("42%08.2zu42\n", 0);
	printf("42%08.2zu42\n", 0);*/

	printf("\n");
	int ret;

	ret = ft_printf(">------------<%-42lc>------------<\n", 'P');
	write(1, "ret=", 4);ft_putnbr(ret);ft_putchar('\n');
	ret = printf(">------------<%-42lc>------------<\n", 'P');
	write(1, "ret=", 4);ft_putnbr(ret);ft_putchar('\n');
	ret = ft_printf("42%46lc42\n", 0);
	write(1, "ret=", 4);ft_putnbr(ret);ft_putchar('\n');
	ret = printf("42%46lc42\n", 0);
	write(1, "ret=", 4);ft_putnbr(ret);ft_putchar('\n');
	return 0;
}
