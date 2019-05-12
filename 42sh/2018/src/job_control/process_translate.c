/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_translate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:32:14 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/27 15:46:10 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "siglist.h"

char	*process_translate_status(int status)
{
	if (status == 0)
		return (NULL);
	if (status == STATUS_FINISHED)
		return (STR_TERMINATED);
	if (status == STATUS_RUNNING)
		return (STR_RUNNING);
	if (status == STATUS_SUSPENDED)
		return (STR_SUSPENDED);
	if (status == STATUS_STOPPED)
		return (STR_STOPPED);
	return (STR_RUNNING);
}
