/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/01 23:39:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void			ft_minishell(void)
{
	int			len;

	prompt(e.env);
	cursor_position(&e.origin);
	ft_memcpy(&e.cursor, &e.origin, sizeof(e.cursor));
	while ((len = read(e.fd, e.buf, READ_SIZE)) > 0)
	{
//		printf("%d %d %d %d %d %d %d %d\n", e.buf[0], e.buf[1], e.buf[2], e.buf[3], e.buf[4], e.buf[5], e.buf[6], e.buf[7]);
		if (K_PRINT)
			read_command(e.buf, len);
		else if (ENTER)
			treat_command();
		else if (KEYPAD || K_SUPPR || CTRL_C)
			keypad_command();
		else if (COPY_KEY)
			copy_command();
		else if (CTRL_D && !*e.hist->cmd)
			break ;
		if (!SHFT_KEY && !CT_SH_KEY && e.cpy.cpy != 0)
			rewrite_command();
		ft_memset(e.buf, 0, len);
	}
}
