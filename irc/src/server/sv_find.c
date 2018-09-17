/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 23:50:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/05 00:00:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_chan			*find_chan(char *name, t_chan *chans)
{
	while (chans)
	{
		if (!sv_strcmp(chans->name, name))
			return (chans);
		chans = chans->next;
	}
	return (NULL);
}
