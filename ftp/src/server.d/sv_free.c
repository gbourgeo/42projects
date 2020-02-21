/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:27:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 15:55:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft.h"
#include "sv_main.h"

void			sv_free_data(t_data *data)
{
	ft_strdel(&data->port);
	ft_close(&data->pasv_fd);
	ft_close(&data->socket);
	if (data->file != MAP_FAILED)
		munmap(data->file, data->fsize);
	data->fsize = -1;
	ft_close(&data->ffd);
}

void			sv_free_login(t_login *login, t_server *sv)
{
	ft_strdel(&login->user);
	login->logged = 0;
	login->member = NULL;
	if (sv)
		login->member = sv_getuserbyname(sv->users, SV_GUEST_NAME);
}

void			sv_free_user(t_user **user)
{
	t_user		*next;

	if (user)
		while (*user)
		{
			ft_strdel(&(*user)->home);
			ft_strdel(&(*user)->name);
			ft_strdel(&(*user)->pass);
			next = (*user)->next;
			ft_bzero(*user, sizeof(**user));
			free(*user);
			*user = next;
		}
}

void			sv_free_env(t_env *env)
{
	if (env->path)
		free(env->path);
	env->path = NULL;
	if (env->home)
		free(env->home);
	env->home = NULL;
}
