/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 05:29:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

/*
** printf("%d %d %d %d %d %d %d %d\n", e->buf[0], e->buf[1], e->buf[2], e->buf[3], e->buf[4], e->buf[5], e->buf[6], e->buf[7]);
**
*/

int				ft_minishell(t_env *e)
{
	int			len;

	prompt(e);
	while ((len = read(e->fd, e->buf, READ_SIZE)) > 0)
	{
// printf("%d %d %d %d %d %d %d %d\n", e->buf[0], e->buf[1], e->buf[2], e->buf[3], e->buf[4], e->buf[5], e->buf[6], e->buf[7]);
		if (KEYPAD(e) || K_SUPPR(e) || CTRL_C(e))
			keypad_command(e);
		else if (COPY_KEY(e))
			copy_command(e);
		else if (CTRL_D(e))
		{
			if (*e->hist->cmd == '\0')
				break ;
		}
		else
			read_command(len, e->buf, e);
		if (!SHFT_KEY(e) && !CT_SH_KEY(e) && e->cpy.cpy != 0)
			rewrite_command(e);
		ft_memset(e->buf, 0, len);
	}
	return (len);
}
