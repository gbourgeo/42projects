/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 02:21:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/14 06:40:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void		sv_cl_prompt(t_fd *cl)
{
	if (cl == NULL)
		return ;
	send(cl->fd, cl->nick, NAME_SIZE, 0);
	send(cl->fd, " \e[32m>\e[0m", 11, 0);
}
