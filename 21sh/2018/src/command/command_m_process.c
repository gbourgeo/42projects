/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_m_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:05:46 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/27 16:05:56 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "command_error.h"
#include "shell_env.h"
#include "shell_lib.h"

int		command_m_process(t_s_env *e, t_jobs *job, int type)
{
	t_m_process		*m_p;
	t_m_process		*curr;

	if (!(m_p = ft_memalloc(sizeof(t_m_process))))
		return (command_error(e->progname, ERR_MALLOC, NULL, e));
	m_p->type = type;
	curr = job->m_process;
	if (!curr)
		job->m_process = m_p;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = m_p;
	}
	job->curr = m_p;
	return (0);
}
