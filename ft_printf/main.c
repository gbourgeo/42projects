/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 10:34:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/16 13:03:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main()
{
	int ret;
	
	ret = ft_printf("%S", L"ç"); printf(" %d\n", ret);
	ret =    printf("%S", L"ç"); printf(" %d\n", ret);
	ret = ft_printf("%S", L"è"); printf(" %d\n", ret);
	ret =    printf("%S", L"è"); printf(" %d\n", ret);
	ret = ft_printf("%S", L"ሴ"); printf(" %d\n", ret);
	ret =    printf("%S", L"ሴ"); printf(" %d\n", ret);
	return 0;
}
