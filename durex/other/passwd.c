/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 22:52:53 by root              #+#    #+#             */
/*   Updated: 2018/08/31 10:28:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "durex.h"

int main(int ac, char **av)
{
	u_char	buff[SERVER_CLIENT_BUFF];
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
		memset(buff + j, 0, SERVER_CLIENT_BUFF - j);
		encryptFunction(buff, j);
		printf("%s (%d):", av[i], j);
		k = 0;
		while (buff[k])
		{
			printf(" %d", buff[k]);
			k++;
		}
		printf("\n");
		i++;
	}
	return 0;
}
