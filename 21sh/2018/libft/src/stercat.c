/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stercat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:21:37 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/26 15:24:01 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*stercat(char *src1, char *src2, char *dest)
{
	int		i;
	int		j;

	i = -1;
	while (src1[++i])
		dest[i] = src1[i];
	j = -1;
	while (src2[++j])
		dest[i + j] = src2[j];
	dest[i + j] = '\0';
	return (dest);
}
