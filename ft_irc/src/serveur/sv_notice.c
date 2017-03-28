/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_notice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 03:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:46:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_notice(char *str, t_fd *cl, t_env *e)
{
	sv_write(":", &e->wr);
	sv_write(e->name, &e->wr);
	sv_write(" NOTICE * :*** ", &e->wr);
	sv_write(str, &e->wr);
	sv_write(END_CHECK, &e->wr);
	sv_cl_send_to(cl, &e->wr);
	e->wr.head = e->wr.tail;
}
