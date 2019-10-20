/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 04:08:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/20 00:43:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

extern char		**environ;

int				ft_init(void *p, size_t size, int type, char *prog)
{
	t_common	*c;

	ft_bzero(p, size);
	c = (t_common *)p;
	c->progpath = prog;
	if (!(c->progname = ft_strrchr(prog, '/')))
		c->progname = prog;
	else
		c->progname++;
	c->progtype = type;
	if ((c->env.path = ft_getenv("PATH=", environ)) == NULL)
		c->env.path = ft_strdup("/usr/local/bin:/usr/bin:/bin");
	if (!c->env.path)
		return (ERR_MALLOC);
	if (!(c->env.home = getcwd(NULL, 0)))
		return (ERR_MALLOC);

	// if ((sv->path = ft_getenv("PATH=", env)) == NULL)
	// 	sv->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	// sv->home = getcwd(NULL, 0);
	// sv->pwd = ft_strdup("");
	// sv->oldpwd = ft_strdup("");
	// if (!sv->path || !sv->home || !sv->pwd || !sv->oldpwd)
	// 	ft_error(ERR_MALLOC, sv);

	// if ((cl->path = ft_getenv("PATH=", env)) == NULL)
	// 	cl->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	// if ((cl->home = ft_strdup(ft_getenv("HOME=", env))) == NULL)
	// 	cl->home = ft_strdup("/");
	// cl->lpwd = getcwd(NULL, 0);
	// if ((cl->oldpwd = ft_strdup(ft_getenv("OLDPWD=", env))) == NULL)
	// 	cl->oldpwd = getcwd(NULL, 0);
	// if ((cl->user = ft_strdup(ft_getenv("USER=", env))) == NULL)
	// 	cl->user = ft_strdup("guest");
	// if (!cl->path || !cl->home || !cl->lpwd || !cl->oldpwd)
	// 	ft_error("ERROR: init_env() failed.");
	return (IS_OK);
}
