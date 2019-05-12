/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_until.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 11:19:47 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/20 11:20:05 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*strdup_until(char *old, char c)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char) * (ft_strlen_ch(old, c) + 1))))
		return (NULL);
	i = 0;
	while (old[i] && old[i] != c)
	{
		str[i] = old[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
