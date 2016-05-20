/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 02:14:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 02:14:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_el				*ft_swap_elems(t_el *elems)
{
	if (elems->prev->prev)
		elems->prev->prev->next = elems;
	if (elems->next)
		elems->next->prev = elems->prev;
	elems->prev->next = elems->next;
	elems->next = elems->prev;
	elems->prev = elems->next->prev;
	elems->next->prev = elems;
	return (elems->prev);
}
