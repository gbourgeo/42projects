/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 17:41:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/25 19:09:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

char		*sv_strchr(const t_buf *b, int c)
{
	char	*tmp;

	tmp = b->head;
	if (tmp && c)
	{
		while (tmp != b->tail && *tmp != c)
		{
			if (tmp > b->end)
				tmp = b->start;
			tmp++;
		}
		if (*tmp == c)
			return (tmp);
	}
	return (NULL);
}
