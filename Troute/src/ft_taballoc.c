/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taballoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 18:13:21 by root              #+#    #+#             */
/*   Updated: 2016/09/14 00:15:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_taballoc(size_t nmemb, size_t size)
{
	void		*ret;

	if (nmemb <= 0 || size <= 0)
		return (NULL);
	ret = (void *)malloc(nmemb);
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, 0, nmemb * size);
	return (ret);
	/* while (nmemb-- > 0) */
	/* { */
	/* 	ret[nmemb] = (void *)malloc(size); */
	/* 	if (ret[nmemb] == NULL) */
	/* 		continue ; */
	/* 	ft_memset(ret[nmemb], 0, size); */
	/* } */
	/* return (ret); */
}
