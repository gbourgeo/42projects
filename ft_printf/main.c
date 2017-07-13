/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:14:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/05 04:03:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// TESTS FOR LIBFTPRINTF.A

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

static void	test(char *str)
{
	int ret1, ret2;

	ret1 = ft_printf(str);
	ret2 = printf("%s", str);
	if (ret1 != ret2) {
		printf("FAIL %d %d\n", ret1, ret2);
		exit(1);
	}
}

int main(void)
{
	int ret1, ret2;
	int tab[] = { 40, 41, 42, 43, 44, 45 };

//	ft_printf(NULL); <-- SEGFAULT
//	printf(NULL); <-- SEGFAULT
	test("TOTO va a l'ecole");
	test("\n");

	ret1 = ft_printf("%s %d %c va a l'ecole\n", "TOTO", 16, 'a');
	ret2 = printf("%s %d %c va a l'ecole\n", "TOTO", 16, 'a');
	printf("%d %d\n", ret1, ret2);

	ret1 = ft_printf("%S %D %C va a l'ecole\n", "TOTO", 16, 'a');
	ret2 = printf("%S %D %C va a l'ecole\n", tab, 16, 'a');
	printf("%d %d\n", ret1, ret2);
	return 0;
}
