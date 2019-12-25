/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:21:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/23 11:28:12 by gbourgeo         ###   ########.fr       */
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
		if (WEXITSTATUS(status))
			return (sv_cmd_err(ft_get_error(WEXITSTATUS(status)), name,
				cl, sv));
		return (sv_cmd_ok("Operation exited normally", cl, sv));
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

	ret = wait4(*pid, &status, WNOHANG, NULL);
	if (ret <= 0)
	{
		if (ret < 0)
			return (ERR_WAIT);
		return (IS_OK);
	}
	if (WIFSTOPPED(status) || WIFCONTINUED(status))
		return (sv_client_write("Operation stopped / continued.\n", cl));
	if (*pid == cl->pid_ls)
		errnb = check_pid_value("ls", status, cl, sv);
	else if (cl->data.function == sv_put)
		errnb = check_pid_value("put", status, cl, sv);
	else if (cl->data.function == sv_get)
		errnb = check_pid_value("get", status, cl, sv);
	*pid = 0;
	return (errnb);
}
