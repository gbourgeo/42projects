/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 04:08:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/30 20:45:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "common.h"

int				ft_init(void *p, int size, char **environ, char *prog)
{
	t_common	*c;
	char		*cwd;

	ft_bzero(p, size);
	c = (t_common *)p;
	c->progpath = prog;
	if (!(c->progname = ft_strrchr(prog, '/')))
		c->progname = prog;
	else
		c->progname++;
	if ((c->env.path = ft_getenv("PATH=", environ)) == NULL)
		c->env.path = ft_strdup("/usr/local/bin:/usr/bin:/bin");
	if (!c->env.path)
		return (ERR_MALLOC);
	if (!(cwd = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	if (cwd[ft_strlen(cwd) - 1] != '/')
	{
		if (!(c->env.home = ft_strjoin(cwd, "/")))
			return (ERR_MALLOC);
		free(cwd);
	}
	else
		c->env.home = cwd;
	return (IS_OK);
}
