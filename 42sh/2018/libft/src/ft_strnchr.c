/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:33:53 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:07:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *str, char c, int n)
{
	int		i;
	int		oc;
	char	*find;

	oc = 0;
	i = -1;
	find = (char*)str;
	while (str[++i])
		if (str[i] == c)
			if (++oc == n)
				break ;
	if (oc == n)
		return (&find[i]);
	return (NULL);
}
