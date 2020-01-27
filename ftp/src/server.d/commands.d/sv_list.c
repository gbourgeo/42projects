/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 02:57:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/27 02:59:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_list(char **cmds, t_client *cl)
{
	
}

int					sv_list_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the name of the current working",
		"directory to be returned in the reply.", NULL
	};

	return (sv_print_help(cl, cmd, "[<pathname>]", help));
}
