/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 14:28:26 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/10 14:33:05 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *chaineSource, int pos, int len)
{ 
	char	*dest;

	dest = NULL;           
	if (len > 0)
	{
		if ((dest = ft_strnew(len + 1)) != NULL)
			ft_strncat(dest, (chaineSource + pos), len);
	}                                       
	return (dest);
}
