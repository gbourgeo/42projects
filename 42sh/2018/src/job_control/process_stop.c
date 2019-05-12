/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_stop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 11:10:26 by dbaffier          #+#    #+#             */
/*   Updated: 2019/03/30 11:18:47 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void	process_stop_all(t_m_process *m_p, int status)
{
	t_process	*p;

	p = m_p->p;
	while (p)
	{
		p->status = status;
		p = p->next;
	}
}
