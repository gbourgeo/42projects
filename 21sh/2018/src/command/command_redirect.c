/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 16:51:52 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "command.h"
#include "command_error.h"

int				command_redirect(int fds[3], t_redirection *redir)
{
	int			fdarg;
	int			fdio;

	ft_memset(fds, 0, 3);
	while (redir)
	{
		fdarg = GET_FD(redir->fdarg);
		fdio = GET_FD(redir->fdio);
		if (command_save_fds(fdarg, fds) || command_save_fds(fdio, fds))
			return (ERR_FCNTL);
		if (fdarg > 0 && dup2(fdarg, fdio) < 0)
			return (ERR_DUP2);
		if (redir->fdio != fdio)
			close(fdio);
		if (fdarg > 0 && redir->fdarg != fdarg)
			close(fdarg);
		redir = redir->next;
	}
	return (ERR_OK);
}
