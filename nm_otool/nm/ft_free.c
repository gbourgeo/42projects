/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 09:06:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/04 21:56:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
