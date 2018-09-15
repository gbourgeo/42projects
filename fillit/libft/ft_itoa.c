/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:29:21 by beborch           #+#    #+#             */
/*   Updated: 2017/11/29 03:41:41 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*int_check(int n)
{
	char	*str;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
	}
	else
	{
		str = ft_strdup("0");
	}
	return (str);
}

static char		*l_itoa(int i, int tmp, int neg, int n)
{
	char	*str;
	int		len;

	while (tmp >= 10)
	{
		tmp = tmp / 10;
		i++;
	}
	i++;
	len = i;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i--;
	while (n >= 10)
	{
		str[i--] = n % 10 + '0';
		n = n / 10;
	}
	if (n < 10)
		str[i] = n % 10 + '0';
	if (neg == 1)
		str[0] = '-';
	str[len] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	int		i;
	int		tmp;
	int		neg;

	i = 0;
	neg = 0;
	if (n == -2147483648 || n == 0)
		return (int_check(n));
	if (n < 0)
	{
		n = n * -1;
		i++;
		neg = 1;
	}
	tmp = n;
	return (l_itoa(i, tmp, neg, n));
}
