/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 22:07:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/19 22:12:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			**ft_tabnew(size_t size)
{
	char		**ret;
	size_t		i;

	ret = NULL;
	i = 0;
	if ((ret = (char **)malloc(sizeof(*ret) * size)) == NULL)
		return (NULL);
	while (i < size)
		ret[i++] = NULL;
	return (ret);
}
