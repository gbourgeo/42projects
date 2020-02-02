/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:44:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/02 02:35:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include "cl_main.h"

int					cl_ncurses_read(t_client *cl)
{
	(void)cl;
	return (IS_OK);
}

// int					cl_stdin_read(t_client *cl)
// {
// 	int			ret;
// 	char		buff[12];
// 	int			i;
// 	int			errnb;

// 	ret = read(STDIN_FILENO, buff, sizeof(buff));
// 	if (ret <= 0)
// 		return (ERR_READ);
// 	i = 0;
// 	errnb = IS_OK;
// 	while (i < ret)
// 	{
// 		if (*buff == 3) // CTRL+C
// 		{
// 			write(STDIN_FILENO, "\n", 1);
// 			cl->rd.len = 0;
// 		}
// 		else if (*buff == 4) // CTRL+D
// 		{
// 			if (cl->rd.len == 0)
// 				return (ERR_QUIT);
// 		}
// 		else if (*buff == 0x7F) // SUPPR.
// 		{
// 			if (cl->rd.len > 0)
// 			{
// 				cl->rd.len--;
// 				tputs(cl_tgetstr("le"), 1, cl_pchar);
// 				tputs(cl_tgetstr("dc"), 1, cl_pchar);
// 			}
// 		}
// 		else if (*buff == 0x0A) // LF
// 		{
// 			if (cl->rd.len)
// 			{
// 				write(STDIN_FILENO, "\n", 1);
// 				errnb = cl_client_commands(cl);
// 				// write(STDIN_FILENO, cl->rd.buff, cl->rd.len);
// 				// write(STDIN_FILENO, "\n", 1);
// 				cl->rd.len = 0;
// 			}
// 		}
// 		else if (buff[i] >= 32 && buff[i] <= 126)
// 		{
// 			if (cl->rd.len < CMD_BUFF_SIZE)
// 			{
// 				cl_pchar(*buff);
// 				*cl->rd.tail++ = buff[i];
// 				cl->rd.len++;
// 			}
// 		}
// 		else
// 		{
// 			// dprintf(0, "%02X", buff[i]);
// 			// fflush(stdin);
// 			// break ;
// 		}
// 		i++;
// 	}
// 	return (errnb);
// }
