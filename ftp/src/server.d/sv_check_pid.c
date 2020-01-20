/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:21:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/21 00:46:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <sys/wait.h>
#include "sv_main.h"

static int		check_pid_value(const char *name, int status, t_client *cl,
t_server *sv)
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
			return (sv_cmd_err("Operation coredump'ed", name, cl, sv));
		return (sv_cmd_err("Operation signal'ed", name, cl, sv));
	}
	return (sv_cmd_err("Unknown error", name, cl, sv));
}

int				sv_check_pid(pid_t *pid, t_client *cl, t_server *sv)
{
	pid_t		ret;
	int			status;
	int			errnb;

	errnb = IS_OK;
	if ((ret = wait4(*pid, &status, WNOHANG, NULL)) <= 0)
		return ((ret < 0) ? ERR_WAIT : IS_OK);
	if (WIFSTOPPED(status) || WIFCONTINUED(status))
		return (sv_client_write("Operation stopped / continued.\n", cl));
	if (*pid == cl->pid_ls)
		errnb = check_pid_value("LIST", status, cl, sv);
	else if (cl->data.function == sv_retr)
		errnb = check_pid_value("RETR", status, cl, sv);
	else if (cl->data.function == sv_stor)
		errnb = check_pid_value("STOR", status, cl, sv);
	*pid = 0;
	return (errnb);
}
