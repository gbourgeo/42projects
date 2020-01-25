/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:56:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_write(const char *str, t_client *cl)
{
	int			i;
	int			ret;

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

int				sv_client_nwrite(const char *str, int len, t_client *cl)
{
	int			i;
	int			ret;

	i = 0;
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
