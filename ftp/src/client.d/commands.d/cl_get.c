/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:17:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/04 22:49:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_get(char *buf, char **cmd, t_client *cl)
{
	(void)buf;
	(void)cmd;
	(void)cl;
	return (IS_OK);
}

int					cl_get_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"", NULL
	};

	return (cl_help_print(cmd, help, cl));
}
