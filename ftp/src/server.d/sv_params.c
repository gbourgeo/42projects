/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:02:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 00:14:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static t_opt	define_opts(char c, char *arg, char *msg, char *info)
{
	return ((t_opt){ { c, arg }, msg, info, NULL});
}

static void		define_all(t_opt *opts)
{
	*opts = define_opts('4', NULL, NULL, "Server allows IpV4 only.");
	(*opts).function = sv_param_four;
	*(opts + 1) = define_opts('6', NULL, NULL, "Every registered users will "
	"have his personal directory created. Works only with \x1B[1m-u\x1B[0m.");
	(*(opts + 1)).function = sv_param_six;
	*(opts + 2) = define_opts('d', NULL, NULL, "Every registered users will "
	"have his personal directory created. Works only with \x1B[1m-u\x1B[0m.");
	(*(opts + 2)).function = sv_param_d;
	*(opts + 3) = define_opts('h', "-help", NULL, "Print help and exit.");
	(*(opts + 3)).function = sv_param_h;
	*(opts + 4) = define_opts('i', NULL, NULL, "Interactive server.");
	(*(opts + 4)).function = sv_param_i;
	*(opts + 5) = define_opts('p', "-path", "[path]", "Server working path.");
	(*(opts + 5)).function = sv_param_p;
	*(opts + 6) = define_opts('u', "-user", NULL, "Enables registered users "
	"mode.");
	(*(opts + 6)).function = sv_param_u;
}

t_opt			*sv_params(int getsize, int tofree)
{
	static t_opt	*opts = NULL;

	if (tofree)
	{
		if (opts)
			free(opts);
		opts = NULL;
		return (NULL);
	}
	if (getsize)
		return ((opts == NULL) ? (t_opt *)0 : (t_opt *)7);
	if (opts != NULL)
		return (opts);
	if ((opts = ft_memalloc(sizeof(*opts) * 7)) == NULL)
		return (NULL);
	define_all(opts);
	return (opts);
}
