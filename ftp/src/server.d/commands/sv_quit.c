/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:46:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 15:48:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_quit(char **cmds, t_server *sv)
{
	(void)cmds;
	(void)sv;
	return (ERR_CLIENT_DISCONNECT);
}
