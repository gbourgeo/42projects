/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:17:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/04 19:38:52 by gbourgeo         ###   ########.fr       */
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
			wprintw(cl->ncu.listwin, "%s", sv->response);
			wrefresh(cl->ncu.listwin);
			sv->wait_response = 0;
			ft_bzero(sv->response, sizeof(sv->response));
			break ;
		}
		else
			i++;
	return (IS_OK);
}
