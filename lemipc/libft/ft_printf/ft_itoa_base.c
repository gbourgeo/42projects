/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:06:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/15 22:36:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char			*ft_itoa_base(ULL nb, ULL base)
{
	char		*b;
	ULL			size;
	ULL			i;
	char		*ret;

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
