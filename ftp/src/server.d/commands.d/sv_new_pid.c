/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:36:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/27 15:39:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_new_pid(char **cmds, t_client *cl, int (*hdlr)())
{
	t_pid		*pid;

	if (!(pid = malloc(sizeof(*pid))))
		return (ERR_MALLOC);
	
}
