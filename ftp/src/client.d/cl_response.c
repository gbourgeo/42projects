/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:17:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/05 19:23:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_response(t_server *sv, t_client *cl)
{
	int			i;

	i = 0;
	while (sv->response[i])
		if (sv->response[i] == '\n')
		{
			sv->response[i] = '\0';
			wprintw(cl->ncu.listwin, "%s\n", sv->response);
			wrefresh(cl->ncu.listwin);
			if (!sv->fct)
				return (IS_OK);
			return (sv->fct(&cl->server, cl));
		}
		else
			i++;
	return (IS_OK);
}
