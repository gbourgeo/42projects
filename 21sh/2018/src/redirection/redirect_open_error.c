/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:30:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 20:58:21 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <limits.h>
#elif __APPLE__
# include <sys/syslimits.h>
#endif
#include "libft.h"
#include "ft_dprintf.h"
#include "shell_env.h"
#include "redirection.h"

int				redirect_open_error(char *filename, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	if (access(filename, F_OK))
		ft_dprintf(STDERR_FILENO, "no such file or directory: ");
	else if (ft_strlen(filename) > NAME_MAX)
		ft_dprintf(STDERR_FILENO, "file name too long: ");
	else
		ft_dprintf(STDERR_FILENO, "permission denied: ");
	ft_dprintf(STDERR_FILENO, "%s\n", filename);
	return (1);
}
