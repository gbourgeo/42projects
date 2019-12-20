/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 00:52:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 01:11:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_new_user(char **data, t_user **next, t_server *sv)
{
	t_user	*user;
	char	*ptr;

	if (!(user = ft_memalloc(sizeof(*user))))
		return (ERR_MALLOC);
	user->type |= (data[0][0] == 'S') ? us_server : us_client;
	if (sv->options & (1 << sv_create_dir))
	{
		if (!(ptr = ft_strjoin(sv->info.env.home, data[1])))
			return (ERR_MALLOC);
		user->home = ft_strjoin(ptr, "/");
		free(ptr);
	}
	else
		user->home = ft_strdup(sv->info.env.home);
	if (!user->home
	|| !(user->name = ft_strdup(data[1]))
	|| !(user->pass = ft_strdup(data[2])))
		return (ERR_MALLOC);
	if ((user->rights = ft_atoi(data[3])) < 0)
		user->rights = 0;
	user->rights = (user->rights > 3) ? 3 : user->rights;
	user->next = *next;
	*next = user;
	return (IS_OK);
}
