/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:06:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 21:35:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char			*ft_itoa_base(unsigned long long nb, unsigned long long base)
{
	char				*b;
	unsigned long long	size;
	unsigned long long	i;
	char				*ret;

	b = "0123456789abcdef";
	size = (nb == 0) ? 1 : 0;
	i = nb;
	while (i)
	{
		size++;
		i /= base;
	}
	if ((ret = ft_strnew(size + 1)) == NULL)
		return (NULL);
	while (size-- > 0)
	{
		ret[size] = b[nb % base];
		nb /= base;
	}
	return (ret);
}
