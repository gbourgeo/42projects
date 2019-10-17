/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 21:41:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_write(char *str, t_client *cl)
{
	int			ret;

	while (str && *str)
	{
		if (cl->wr.len == BUFF_SIZE)
			if ((ret = sv_client_send(cl)) != IS_OK)
				return (ret);
		*cl->wr.tail++ = *str;
		if (cl->wr.tail >= cl->wr.buff + BUFF_SIZE)
			cl->wr.tail = cl->wr.buff;
		cl->wr.len++;
		str++;
	}
	return (IS_OK);
}
