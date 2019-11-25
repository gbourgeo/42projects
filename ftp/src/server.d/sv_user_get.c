/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:45:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/25 02:15:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_user			*sv_getuserbyname(t_user *users, const char *name)
{
	while (users)
		if (ft_strequ(users->name, name))
			return (users);
		else
			users = users->next;
	return (NULL);
}

int				sv_getcommandsright(int rights)
{
	if (rights < 1)
		return (3);
	if (rights < 2)
		return (6);
	if (rights < 3)
		return (9);
	return (10);
}
