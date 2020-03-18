/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:16:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:18:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

char			*sv_client_home(const char *dir, t_user *us, t_server *sv)
{
	if (sv->options & (1 << sv_user_mode))
		while (us)
		{
			if (!ft_strcmp(us->name, dir))
				return (us->home);
			else
				us = us->next;
		}
	return (sv->info.env.home);
}
