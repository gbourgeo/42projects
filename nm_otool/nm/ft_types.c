/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 04:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/07 15:16:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char			ft_more(unsigned int i, t_sec *sect)
{
	if (i > 0 && i <= sect->size)
	{
		if (!ft_strcmp(sect->sec[i - 1], SECT_DATA))
			return ('D');
		else if (!ft_strcmp(sect->sec[i - 1], SECT_BSS))
			return ('B');
		else if (!ft_strcmp(sect->sec[i - 1], SECT_TEXT))
			return ('T');
	}
	return ('S');
}

unsigned char		ft_get_type(t_el *el, t_base *env)
{
	unsigned char	ret;

	ret = '?';
	if ((el->n_type & N_TYPE) == N_UNDF)
		ret = (el->n_value) ? 'C' : 'U';
	else if ((el->n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((el->n_type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((el->n_type & N_TYPE) == N_SECT)
		ret = ft_more(el->n_sect, &env->sect);
	else if ((el->n_type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((el->n_type & N_STAB) != 0)
		ret = '-';
	if ((el->n_type & N_EXT) == 0 && ret != '?' && ret != '-')
		ret += 32;
	return (ret);
}
