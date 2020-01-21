/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:21:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/21 01:03:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <sys/wait.h>
#include "sv_main.h"

static int		check_pid_value(const char *name, int status, t_client *cl)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status)
			return (sv_response(cl, " %s:%s", name, ft_get_error(status)));
		if (name)
			return (sv_response(cl, "%s Successfully %s",
			(!ft_strcmp(name, "LIST")) ? "212" : "250", name));
		return (sv_response(cl, "200 Command complete"));
	}
	else if (WIFSIGNALED(status))
	{
		if (HAS_WCOREDUMP && WCOREDUMP(status))
			return (sv_response(cl, "510 %s Operation coredump'ed", name));
		return (sv_response(cl, "511 %s Operation signal'ed", name));
	}
	return (sv_response(cl, "512 %s Unknown error", name));
}

int				sv_check_pid(pid_t *pid, t_client *cl)
{
	pid_t		ret;
	int			status;
	int			errnb;

	errnb = IS_OK;
	if ((ret = wait4(*pid, &status, WNOHANG, NULL)) <= 0)
		return ((ret < 0) ? ERR_WAIT : IS_OK);
	if (WIFSTOPPED(status) || WIFCONTINUED(status))
		return (sv_response(cl, "451 Operation stopped / continued.\n", cl));
	if (*pid == cl->pid_ls)
		errnb = check_pid_value("LIST", status, cl);
	else if (cl->data.function == sv_retr)
		errnb = check_pid_value("RETR", status, cl);
	else if (cl->data.function == sv_stor)
		errnb = check_pid_value("STOR", status, cl);
	*pid = 0;
	return (errnb);
}
