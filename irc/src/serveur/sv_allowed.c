/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_allowed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 08:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:39:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_user			*sv_allowed(t_info *inf, t_user *ptr)
{
	while (ptr)
	{
		if (!*ptr->port || !ft_strcmp(ptr->port, inf->port))
		{
			if (ft_strchr(ptr->hostname, '*'))
			{
				if (!sv_globcmp(ptr->hostname, inf->host))
					break ;
			}
			else if (!ft_strcmp(ptr->hostname, inf->host))
				break ;
			if (ft_strchr(ptr->hostaddr, '*'))
			{
				if (!sv_globcmp(ptr->hostaddr, inf->addr))
					break ;
			}
			else if (!ft_strcmp(ptr->hostaddr, inf->addr))
				break ;
		}
		ptr = ptr->next;
	}
	return (ptr);
}
