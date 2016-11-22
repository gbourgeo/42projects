/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 04:01:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/12 04:22:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>

static int		sv_size(char *str)
{
	int			i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void			sv_err(char *nick, char *err, int fd)
{
	send(fd, nick, sv_size(nick), 0);
	send(fd, " ", 1, 0);
	send(fd, err, sv_size(err), 0);
	send(fd, "\r\n", 2, 0);
}
