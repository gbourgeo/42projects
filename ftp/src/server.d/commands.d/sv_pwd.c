/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 21:04:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 02:39:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_pwd(char **cmds, t_client *cl, t_server *sv)
{
	int			ret;

	(void)cmds;
	(void)sv;
	if ((ret = sv_client_write(cl->pwd, cl)) != IS_OK
	|| (ret = sv_client_write("\n", cl)) != IS_OK)
		return (ret);
	return (sv_cmd_ok("Successfully printed working directory", cl, sv));
}
