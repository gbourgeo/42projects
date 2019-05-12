/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup_until.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:11:28 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/29 19:37:13 by rfontain         ###   ########.fr       */
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
	ret[i] = '\0';
	return (ret);
}
