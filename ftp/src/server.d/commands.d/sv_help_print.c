/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 12:30:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 16:47:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_print_help(t_client *cl, t_command *cmd, char *args,
char **description)
{
	long	i;
	int		errnb;

	i = 0;
	errnb = sv_response(cl, "\r\nCommand: %s %s\r\n", cmd->name, args);
	while (errnb == IS_OK && description[i])
	{
		errnb = sv_response(cl, "%s", description[i]);
		i++;
	}
	return (errnb);

}
