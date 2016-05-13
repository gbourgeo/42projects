/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:57:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/13 12:58:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				ft_free_arc(t_arc **arc)
{
	if (*arc == NULL)
		return ;
	if ((*arc)->next)
		ft_free_arc(&(*arc)->next);
	ft_memset(*arc, '\0', sizeof(**arc));
	free(*arc);
	*arc = NULL;
}
