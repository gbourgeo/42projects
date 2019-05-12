/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 06:41:46 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/19 06:41:48 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int i)
{
	char *str;

	str = ft_strjoin(s1, s2);
	if (i == 1)
		free(s1);
	else if (i == 2)
		free(s2);
	else if (i == 3)
	{
		free(s1);
		free(s2);
	}
	return (str);
}
