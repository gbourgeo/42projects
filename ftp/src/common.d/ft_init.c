/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 04:08:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 03:06:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "common.h"

int				ft_init(void *p, int size, char **environ, char *prog)
{
	t_common	*c;

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
	if (!(c->env.home = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	return (IS_OK);
}
