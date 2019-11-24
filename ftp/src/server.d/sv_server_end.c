/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:53:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/24 18:54:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_server_end(t_server *sv)
{
	sv_server_close(sv_v4, (int[2]){-1, -1}, sv);
	sv_server_close(sv_v6, (int[2]){-1, -1}, sv);
	sv_free_env(&sv->info.env);
	sv_free_user(&sv->users);
}
