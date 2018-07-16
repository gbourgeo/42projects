/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 22:52:53 by root              #+#    #+#             */
/*   Updated: 2018/07/16 23:20:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "durex.h"

int main(int ac, char **av)
{
	char	buff[CLIENT_BUFF];
	int		i, j, k;
	char	*ptr;

	if (ac == 1)
		return 1;
	i = 1;
	while (av[i])
	{
		ptr = av[i];
		j = 0;
		while (ptr[j])
		{
			buff[j] = ptr[j];
			j++;
		}
		buff[j] = '\0';
		encrypt(buff, j);
		printf("%s (%d): ", av[i], j);
		k = 0;
		while (k < 8)
		{
			printf("%d,", buff[k]);
			k++;
		}
		printf("\n");
		i++;
	}
	return 0;
}
