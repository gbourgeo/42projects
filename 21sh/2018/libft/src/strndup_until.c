/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup_until.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:21:06 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/29 19:21:08 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int nb)
{
	int		i;
	char	*ret;

	if (!(ret = (char*)malloc(sizeof(char) * (nb + 1))))
		return (NULL);
	i = 0;
	while (str[i] && i < nb)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}
