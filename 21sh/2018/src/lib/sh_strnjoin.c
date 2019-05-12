/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 23:35:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 21:03:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

char			*sh_strnjoin(const char *s1, const char *s2, size_t len)
{
	char		*ret;

	if (!(ret = ft_memalloc(len + ft_strlen(s2) + 1)))
		return (NULL);
	ret = ft_strncpy(ret, s1, len);
	ret = ft_strcat(ret, s2);
	return (ret);
}
