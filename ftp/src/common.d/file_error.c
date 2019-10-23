/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 18:33:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/16 20:50:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include "libft.h"

int				file_error(char *msg, t_envi *e, int caller, int do_send)
{
	if (caller == CLIENT || (caller == SERVER && e->success == 1))
	{
		ft_putstr("\033[31m");
		ft_putstr(msg);
		ft_putstr("\033[0m");
		ft_putchar('\n');
	}
	if (do_send)
		send(e->fd, msg, ft_strlen(msg), 0);
	return (1);
}
