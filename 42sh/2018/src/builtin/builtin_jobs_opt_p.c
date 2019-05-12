/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_opt_p.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:09:58 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/11 16:24:36 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_jobs.h"
#include "job_control.h"
#include "ft_printf.h"

void		job_opt_p(const t_jobs *job)
{
	ft_printf("%d\n", job->pgid);
}
