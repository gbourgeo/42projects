/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:30:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/28 17:34:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_print_help(t_client *cl, t_command *cmd, char *args,
char **description)
{
	long	i;
	int		errnb;

	i = 0;
	errnb = sv_response(cl, " Command: %s %s", cmd->name, args);
	while (errnb == IS_OK && description[i])
	{
		errnb = sv_response(cl, "\t%s", description[i]);
		i++;
	}
	errnb = sv_response(cl, "");
	return (errnb);

}
