/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 19:53:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/03 23:09:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*p;
	int		sign;
	int		i;
	int		src;

	src = n;
	i = (n < 0 ? 3 : 2);
	while ((n /= 10))
		++i;
	if ((p = (char*)malloc(sizeof(*p) * i)) == NULL)
		return (NULL);
	p[--i] = '\0';
	if (src == 0)
		p[0] = '0';
	if ((sign = (src < 0 ? -1 : 1)) < 0)
		p[0] = '-';
	while (src != 0)
	{
		p[--i] = ((src % 10) * sign + 48);
		src /= 10;
	}
	return (p);
}
