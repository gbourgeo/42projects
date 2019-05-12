/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 17:38:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/06 18:39:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_normal_keys(char *buf, t_env *e)
{
	int		len;

	len = e->pos + ft_strlen(buf);
	if ((len >= CMD_SIZE) || (len % CMD_SIZE == 0))
		e->history->command = ft_realloc(e->history->command, CMD_SIZE);
	ft_stricpy(e->history->command, buf, e->pos);
	ft_putstr(buf);
	e->pos += len - e->pos;
}
