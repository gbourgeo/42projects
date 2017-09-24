/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/09/24 07:07:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_malloc.h"
#include <string.h>

void		print(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr;
	char	*test;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	test = realloc((void *)addr + 5, 10);
	if (test == NULL)
		print("Bonjours\n");
	return (0);
}
