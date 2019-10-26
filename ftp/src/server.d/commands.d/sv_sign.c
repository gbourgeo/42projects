/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 03:15:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** Hash the password receoived, compare it to the pass stored.
** Change the user cwd.
*/

static int			get_password(t_client *cl)
{
	int			errnb;

	if ((errnb = send(cl->fd, "Pass: ", 6, 0)) <= 0)
		return ((errnb) ? ERR_RECV : ERR_DISCONNECT);
	return (IS_OK);
}

int					sv_sign(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*ptr;
	int			errnb;

	if (!cmds[1] || !cmds[1][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	ptr = sv->users;
	while (ptr)
	{
		if (!ft_strcmp(cmds[1], ptr->name))
			if ((errnb = get_password(cl)) == IS_OK)
				return (sv_client_write(SERVER_OK_OUTPUT, cl));
		ptr = ptr->next;
	}
	return (sv_cmd_err(ft_get_error(ERR_INVALID_NAMEPASS), cmds[0], cl, sv));
}
