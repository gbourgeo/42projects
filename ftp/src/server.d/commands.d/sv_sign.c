/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 02:06:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_sign(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*ptr;

	if (!cmds[1] || !cmds[1][0] || !cmds[2] || !cmds[2][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	ptr = sv->users;
	while (ptr)
	{
		if (!ft_strcmp(cmds[1], ptr->name))
			if (!ft_strcmp(cmds[2], ptr->pass))
			{
				// Hash the password receoived, compare it to the pass stored.

				// Change the user cwd.
return (ERR_MALLOC);
				return (sv_client_write(SERVER_OK_OUTPUT, cl));
			}
		ptr = ptr->next;
	}
	return (sv_cmd_err(ft_get_error(ERR_INVALID_NAMEPASS), cmds[0], cl, sv));
}
