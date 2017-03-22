/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:41:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 17:44:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_chan			*check_safe_channel(char *name, t_fd *cl, t_env *e)
{
	chan = e->chans;
	while (chan && sv_strcmp(list[i], chan->name))
		chan = chan->next;
}

t_chan			*check_normal_channel(char *name, t_fd *cl, t_env *e)
{
	chan = e->chans;
	while (chan && sv_strcmp(list[i], chan->name))
		chan = chan->next;
}
