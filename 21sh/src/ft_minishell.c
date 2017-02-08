/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 23:41:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void			ft_minishell(t_env *e)
{
	int			len;

	prompt(e->env);
	cursor_position(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	while ((len = read(e->fd, e->buf, READ_SIZE)) > 0)
	{

//		printf("%d %d %d %d %d %d %d %d\n", e->buf[0], e->buf[1], e->buf[2], e->buf[3], e->buf[4], e->buf[5], e->buf[6], e->buf[7]);
		if (K_PRINT(e))
			read_command(len, e);
		else if (ENTER(e))
			treat_command(e);
		else if (KEYPAD(e) || K_SUPPR(e) || CTRL_C(e))
			keypad_command(e);
		else if (COPY_KEY(e))
			copy_command(e);
		else if (CTRL_D(e) && !*e->hist->cmd)
			break ;
		if (!SHFT_KEY(e) && !CT_SH_KEY(e) && e->cpy.cpy != 0)
			rewrite_command(e->hist->cmd, e);
		ft_memset(e->buf, 0, len);
	}
}
