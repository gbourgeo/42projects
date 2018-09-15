/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 01:06:57 by beborch           #+#    #+#             */
/*   Updated: 2017/12/29 15:30:35 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *meule_de_foin, const char *aiguille)
{
	int i;

	i = 0;
	if (!ft_strlen(aiguille))
		return ((char*)meule_de_foin);
	while (meule_de_foin[i])
	{
		if (ft_strncmp(aiguille, &meule_de_foin[i], ft_strlen(aiguille)) == 0)
			return ((char *)&meule_de_foin[i]);
		i++;
	}
	return (NULL);
}
