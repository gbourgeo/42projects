/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 23:18:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 09:52:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_end(char **cmds, t_envi *sv)
{
	if (cmds)
		ft_free(&cmds);
	if (sv->rec == -1 && sv->success)
		ft_putendl_fd("ERROR: server: recv() failed.", 2);
	if (sv->success)
		ft_putendl("\033[31mSERVEUR: A client has disconnected\033[0m");
	close(sv->fd);
	close(sv->ip[v4]);
	close(sv->ip[v6]);
	ft_bzero(sv->buff, BUFF_SIZE + 1);
	ft_bzero(sv->data, DATA_SIZE + 1);
	free(sv->home);
	free(sv->pwd);
	free(sv->oldpwd);
	exit(sv->rec);
	return (sv->rec);
}
