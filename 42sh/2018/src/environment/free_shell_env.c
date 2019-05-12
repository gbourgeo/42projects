/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:23:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 17:24:01 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "shell_lib.h"
#include "shell_env.h"
#include "command.h"

static void		free_aliases(t_alias *alias)
{
	if (!alias)
		return ;
	free_aliases(alias->next);
	if (alias->key)
		free(alias->key);
	if (alias->value)
		free(alias->value);
	free(alias);
}

static void		free_proc(t_process *p)
{
	if (p)
	{
		command_free((t_execute *)p->exec, NULL);
		p->exec = NULL;
		free(p->next);
		free(p);
	}
}

static void		free_m_process(t_m_process *p)
{
	if (p)
	{
		free_proc(p->p);
		free_m_process(p->next);
		free(p);
	}
}

static void		free_jobs(t_jobs *job)
{
	if (job)
	{
		free_m_process(job->m_process);
		free(job->cmd_name);
		free_jobs(job->next);
		free(job);
	}
}

void			free_shell_env(t_s_env *e)
{
	if (e->interactive)
		close(e->fd);
	if (e->progpath)
		free(e->progpath);
	sh_freetab(&e->public_env);
	sh_freetab(&e->private_env);
	sh_freetab(&e->exported_env);
	free_aliases(e->alias_list);
	free_jobs(e->jobs);
}
