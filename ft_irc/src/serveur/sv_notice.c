/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_notice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 03:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 03:21:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_notice(int fd, char *str, t_env *e)
{
	send(fd, e->name, SERVER_LEN, 0);
	send(fd, " NOTICE * :*** ", 15, 0);
	send(fd, str, ft_strlen(str), 0);
	send(fd, END_CHECK, END_CHECK_LEN, 0);
}
