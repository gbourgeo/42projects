/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 18:34:59 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/26 18:35:01 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_reverse(char *s, int j)
{
	char	*tmp;
	int		i;
	int		k;

	k = 0;
	i = ft_strlen(s);
	if (j % 2 != 0)
	{
		tmp = (char *)malloc(sizeof(char) * (i + 2));
		tmp[k++] = '-';
	}
	else
		tmp = (char *)malloc(sizeof(char) * (i + 1));
	while (i--)
		tmp[k++] = s[i];
	tmp[k] = '\0';
	return (tmp);
}

size_t		ft_intlen(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		tmp;
	int		j;

	i = 0;
	j = 0;
	if ((s = (char *)malloc(sizeof(char) * ft_intlen(n))) == NULL)
		return (0);
	if (n < 0)
	{
		j++;
		n = n * -1;
	}
	if (n == 0)
		s[i++] = '0';
	while (n != 0)
	{
		tmp = n % 10;
		s[i++] = tmp + '0';
		n = n / 10;
	}
	s[i] = '\0';
	return (ft_reverse(s, j));
}
