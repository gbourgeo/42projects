/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:34:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/18 08:20:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

int main()
{
	int ret;
	
	setlocale(LC_ALL, "");
	ret = ft_printf("%S", L"ç"); printf(" %d\n", ret);
	ret = ft_printf("%{%30S}", L"èèèèè"); printf(" %d\n", ret);
	ret =    printf("%{%30S}", L"èèèèè"); printf(" %d\n", ret);
	ret = ft_printf("%S", L"A ሴሴሴሴሴሴ"); printf(" %d\n", ret);
	ret = ft_printf("%p", 0); printf(" %d\n", ret);
	ret =    printf("%p", 0); printf(" %d\n", ret);	
	ret = ft_printf("{%30S}", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("{%30S}", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("{%05p}", 0); printf(" %d\n", ret);
	ret =    printf("{%05p}", 0); printf(" %d\n", ret);
	ret = ft_printf("%15.4d", -42); printf(" %d\n", ret);
	ret =    printf("%15.4d", -42); printf(" %d\n", ret);
	ret = ft_printf("%.4S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("%.4S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("%.2S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("%.2S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("%.0S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("%.0S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("%.S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("%.S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("%.100S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("%.100S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("%15.4S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret =    printf("%15.4S", L"ሴሴሴሴሴሴ "); printf(" %d\n", ret);
	ret = ft_printf("%4.1S", L"Jambon"); printf(" %d\n", ret);
	ret =    printf("%4.1S", L"Jambon"); printf(" %d\n", ret);
	ret = ft_printf("%c", 200); printf(" %d\n", ret);
	ret =    printf("%c", 200); printf(" %d\n", ret);

	return 0;
}
