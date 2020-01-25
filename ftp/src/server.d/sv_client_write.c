/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 16:29:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_write(const char *str, t_client *cl)
{
	int			i;
	int			ret;

// printf("%s\n", str);
// printf("Write: len:%ld buff:%p head:%p tail:%p\n", cl->wr.len, cl->wr.buff, cl->wr.head, cl->wr.tail);
	i = 0;
	if (str)
		while (str[i])
		{
			if (cl->wr.len == CMD_BUFF_SIZE)
				if ((ret = sv_client_send(cl)) != IS_OK)
					return (ret);
			*cl->wr.tail++ = str[i];
			if (cl->wr.tail >= cl->wr.buff + CMD_BUFF_SIZE)
				cl->wr.tail = cl->wr.buff;
			cl->wr.len++;
			i++;
		}
	return (IS_OK);
}
#include <unistd.h>
int				sv_client_nwrite(const char *str, int len, t_client *cl)
{
	int			i;
	int			ret;

	i = 0;
// write(1, str, len); write(1, "\n", 1);
// printf("NWrite: len:%ld buff:%p head:%p tail:%p\n", cl->wr.len, cl->wr.buff, cl->wr.head, cl->wr.tail);
	if (str)
		while (i < len && str[i])
		{
			if (cl->wr.len == CMD_BUFF_SIZE)
				if ((ret = sv_client_send(cl)) != IS_OK)
					return (ret);
			*cl->wr.tail++ = str[i];
			if (cl->wr.tail >= cl->wr.buff + CMD_BUFF_SIZE)
				cl->wr.tail = cl->wr.buff;
			cl->wr.len++;
			i++;
		}
	return (IS_OK);
}
