/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_notice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 03:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 03:59:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_notice(char *str, t_fd *cl)
{
	sv_cl_write(":", cl);
	sv_cl_write(e.name, cl);
	sv_cl_write(" NOTICE * :*** ", cl);
	sv_cl_write(str, cl);
	sv_cl_write(END_CHECK, cl);
}
