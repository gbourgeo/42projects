/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_restore_fds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 00:02:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 17:00:21 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "redirection.h"
#include "command.h"

int				command_restore_fds(int fds[3])
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < 3)
	{
		if (fds[i] > 0)
		{
			if (dup2(fds[i], i) < 0)
				ret = 1;
			if (fds[i] != -1)
				close(fds[i]);
		}
		i++;
	}
	return (ret);
}
