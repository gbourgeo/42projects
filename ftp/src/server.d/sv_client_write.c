/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 22:47:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_write(const char *str, t_client *cl)
{
	int			ret;

	while (str && *str)
	{
		if (cl->wr.len == CMD_BUFF_SIZE)
			if ((ret = sv_client_send(cl)) != IS_OK)
				return (ret);
		*cl->wr.tail++ = *str;
		if (cl->wr.tail >= cl->wr.buff + CMD_BUFF_SIZE)
			cl->wr.tail = cl->wr.buff;
		cl->wr.len++;
		str++;
	}
	return (IS_OK);
}
