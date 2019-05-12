/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 16:55:52 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control.h"
#include "command.h"
#include "operator_types.h"
#include "expansion.h"
#include "redirection.h"

static int		prepare_redirect(t_redirection *cmd, t_s_env *e, t_jobs *job)
{
	if (!cmd)
		return (0);
	if (expand_argument(cmd->arg, e, 0))
		return (1);
	quote_removal(cmd->arg);
	cmd->async = job->foreground;
	if (job->foreground == 0 && redirection(&cmd, e))
		return (1);
	return (prepare_redirect(cmd->next, e, job));
}

static int		prepare_command(void *cmd, t_s_env *e, t_jobs *job)
{
	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (prepare_command(((t_pipeline *)cmd)->left, e, job)
			|| prepare_command(((t_pipeline *)cmd)->right, e, job));
	else if ((expand_argument(((t_command *)cmd)->args, e, 1)
		|| prepare_redirect(((t_command *)cmd)->redir, e, job)))
		return (1);
	quote_removal(((t_command *)cmd)->args);
	return (0);
}

static int		execute_ao_list(t_ao_list *aolist,
		t_s_env *e, t_jobs *job)
{
	if (!aolist)
		return (0);
	if (!command_m_process(e, job, aolist->type)
		&& !prepare_command(aolist->cmd, e, job))
		command_parse(aolist->cmd, e, aolist->type);
	return (execute_ao_list(aolist->next, e, job));
}

int				execute_list(t_m_list *list, t_s_env *e)
{
	t_jobs	*job;

	if (!list || e->shell_loop == 0)
		return (0);
	job = jobs_prepare(e);
	job->status |= JOB_CURR;
	job->cmd_name = get_command(list);
	job->foreground = list->async;
	if (execute_ao_list(list->aolist, e, job))
		return (1);
	if (!e->err_exp)
		command_job(job, e);
	else
		job->status |= JOB_NOTIFIED;
	e->err_exp = 0;
	return (execute_list(list->next, e));
}
