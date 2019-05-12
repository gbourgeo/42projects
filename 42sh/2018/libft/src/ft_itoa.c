/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 04:09:04 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/08 12:09:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strrev_itoa(char *str, int i)
{
	int		j;
	char	*rev;

	j = 0;
	rev = (char*)malloc(sizeof(char) * 13);
	if (str[0] == '-')
	{
		rev[0] = str[0];
		j++;
	}
	while (i >= 0 && str[i] != '-')
		rev[j++] = str[i--];
	rev[j] = '\0';
	return (rev);
}

char			*ft_itoa(int n)
{
	char	str[12];
	int		i;

	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		if (n == -2147483648)
		{
			str[i++] = '8';
			n /= 10;
		}
		n *= -1;
	}
	if (n == 0)
		str[i++] = '0';
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	str[i] = '\0';
	return (ft_strrev_itoa(str, i - 1));
}
