/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:21:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 03:31:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <sys/wait.h>
#include "sv_main.h"

int				sv_check_pid(pid_t *pid, t_client *cl)
{
	pid_t		ret;
	int			status;

	ret = wait4(*pid, &status, WNOHANG, NULL);
	if (ret <= 0)
	{
		if (ret < 0)
			return (ERR_WAIT);
		return (IS_OK);
	}
	if (WIFEXITED(status))
		cl->errnb[0] = (WEXITSTATUS(status)) ?
			sv_client_write(ERR_OUTPUT, cl) :
			sv_client_write(OK_OUTPUT, cl);
	else if (WIFSIGNALED(status))
		cl->errnb[0] = sv_client_write(ERR_OUTPUT, cl);
	else if (HAS_WCOREDUMP && WCOREDUMP(status))
		cl->errnb[0] = sv_client_write(ERR_OUTPUT, cl);
	else if (WSTOPSIG(status) || WIFCONTINUED(status))
		return (IS_OK);
	*pid = 0;
	return (IS_OK);
}
