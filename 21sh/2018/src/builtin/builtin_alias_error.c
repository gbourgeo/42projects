/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 03:01:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 12:37:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "builtin_alias.h"

int		alias_error(int err, const char *cmd, const char *key, t_s_env *e)
{
	static char	*errors[] = {
		NULL, "malloc failed", "Bad file descriptor",
		"not found", "key not valid",
	};

	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", cmd, key, errors[err]);
	return (1);
}
