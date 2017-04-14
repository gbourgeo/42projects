/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 17:02:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/21 18:07:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_stricpy(char *s1, const char *s2, int pos)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL || pos > (int)ft_strlen(s1))
		return ;
	if (s1[pos] != '\0')
	{
		i = ft_strlen(s1 + pos);
		while (i > 0)
		{
			s1[pos + i + j - 1] = s1[pos + i - 1];
			i--;
		}
	}
	while (s2[i] != 0)
	{
		s1[pos + i] = s2[i];
		i++;
	}
}
