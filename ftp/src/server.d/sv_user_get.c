/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:45:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 21:23:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_user			*sv_getuserbyname(t_user *users, const char *name)
{
	if (name)
		while (users)
		{
			if (ft_strequ(users->name, name))
				return (users);
			else
				users = users->next;
		}
	return (NULL);
}
