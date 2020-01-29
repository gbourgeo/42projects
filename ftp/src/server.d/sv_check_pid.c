/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:21:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/29 18:01:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <sys/wait.h>
#include "sv_main.h"

static int		check_pid_value(const char *name, int status, t_client *cl)
{
	cl->data.pid = -1;
	ft_close(&cl->data.pasv_fd);
	ft_close(&cl->data.socket);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status)
			return (sv_response(cl, "512 Internal error (%s)", ft_get_error(status)));
		if (name)
			return (sv_response(cl, "%s %s OK",
			(!ft_strcmp(name, "LIST")) ? "212" : "250", name));
		return (sv_response(cl, "200 Command OK"));
	}
	else if (WIFSIGNALED(status))
	{
		if (HAS_WCOREDUMP && WCOREDUMP(status))
			return (sv_response(cl, "510 %s Operation coredump'ed", name));
		return (sv_response(cl, "511 %s Operation signal'ed", name));
	}
	return (sv_response(cl, "512 %s Unknown error", name));
}

int				sv_check_pid(t_client *cl)
{
	pid_t		ret;
	int			status;
	int			errnb;

	errnb = IS_OK;
	if ((ret = wait4(cl->data.pid, &status, WNOHANG, NULL)) <= 0)
		return ((ret < 0) ? ERR_WAIT : IS_OK);
	if (WIFSTOPPED(status) || WIFCONTINUED(status))
		return (sv_response(cl, "451 Operation stopped / continued.\n", cl));
	if (ret == cl->data.pid)
		errnb = check_pid_value("TEST", status, cl);
	return (errnb);
}
