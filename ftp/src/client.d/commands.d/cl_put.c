/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/17 02:32:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_put(char *buf, char **cmd, t_client *cl)
{
	(void)buf;
	(void)cmd;
	(void)cl;
	return (IS_OK);
}

int				cl_put_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the user to send a file to the server.", NULL
	};

	return (cl_help_print(cmd, "[<file_name / file_path>]", help, cl));
}
