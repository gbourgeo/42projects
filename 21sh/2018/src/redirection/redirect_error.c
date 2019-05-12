/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:29:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 16:47:28 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "shell_env.h"
#include "redirection_errors.h"
#include "redirection.h"

int				redirect_error(int err, char *redirect_arg, t_s_env *e)
{
	static char	*error[] = {
		NULL,
		MALLOC_STR,
		AMBIGOUS_STR,
		EXISTING_STR,
		BAD_FD_STR
	};

	*e->ret = 130;
	if (err == ERR_FREE_ALL)
		return (1);
	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", redirect_arg, error[err]);
	*e->ret = 2;
	return (1);
}
