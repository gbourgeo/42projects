/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 22:56:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/11 22:59:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "\x1B[6n"	is a code to send to the terminal to receive the position
**				of the cursor.
**				The reponse is in the form : \x1B[yy;xx
**				where 'yy' is the line number and 'xx is the column number.
**				Example: \x1B[32;54
*/

void			cursor_position(t_pos *pos)
{
	char		buf[11];
	int			l;
	char		*str;

	write(data.fd, "\x1B[6n", 4);
	if ((l = read(data.fd, buf, 11)) < 0)
		ft_exit_all("Cursor position read failed.");
	if ((str = ft_strchr(buf, '[')) == NULL)
		ft_exit_all("Cursor position data corrupted ('[' missing)");
	pos->y = ft_atoi(str + 1) - 1;
	if ((str = ft_strchr(buf, ';')) == NULL)
		ft_exit_all("Cursor position data corrupted (';' missing)");
	pos->x = ft_atoi(str + 1) - 1;
}
