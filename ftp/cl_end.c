/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 20:09:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 08:11:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_end(char *msg, t_envi *cl)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	close(cl->fd);
	ft_bzero(cl->buff, BUFF_SIZE + 1);
	ft_bzero(cl->data, DATA_SIZE + 1);
	free(cl->user);
	free(cl->path);
	free(cl->home);
	free(cl->lpwd);
	free(cl->oldpwd);
	ft_putendl_fd("\033[34m ~ Bye ~", 2);
	exit(cl->success);
	return (0);
}
