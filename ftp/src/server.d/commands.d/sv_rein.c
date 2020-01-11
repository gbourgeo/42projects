/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rein.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:19:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 18:36:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_rein(char **cmds, t_client *cl, t_server *sv)
{
	(void)cmds;
	sv_free_login(&cl->login);
	return (sv_cmd_ok("Reinitialized user", cl, sv));
}
