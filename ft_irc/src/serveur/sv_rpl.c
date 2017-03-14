/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rpl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 01:44:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 02:00:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void				sv_rpl(char *num, char *cmd, char *cmd2, t_fd *cl, t_env *e)
{
	static char		*rpl[] = { { NULL, NULL, NULL }, //300
							   { cmd, " :", cmd2 }, //
							   { NULL, NULL, NULL } };
	int				pos;

	if (ft_strlen(num) != 3 || *num != '3')
		return ;
}
