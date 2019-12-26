/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:37:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 18:49:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		only_positive_number(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	return (1);
}

static int		get_value(char **av, t_param *p, t_server *sv)
{
	size_t		j;
	size_t		k;
	int			errnb;

	j = 0;
	while (av[p->i][++j])
	{
		k = -1;
		while (++k < p->size)
			if (av[p->i][j] == p->opts[k].c
			|| (p->opts[k].str
				&& ft_strequ(&av[p->i][j], p->opts[k].str)))
			{
				if ((errnb = p->opts[k].function(av, &p->i, sv)) != IS_OK)
					return (errnb);
				if (p->opts[k].param
				|| (p->opts[k].str
					&& ft_strequ(&av[p->i][j], p->opts[k].str)))
					return (IS_OK);
				break ;
			}
		if (k == p->size)
			return (ERR_WRONG_PARAM);
	}
	return (IS_OK);
}

int				sv_params_get(char **av, t_server *sv)
{
	t_param		p;
	int			errnb;

	p.opts = sv_params(0);
	p.size = (size_t)sv_params(1);
	p.i = 1;
	sv->options |= ((1 << sv_v4) | (1 << sv_v6));
	while (av[p.i])
	{
		if (av[p.i][0] == '-')
		{
			if ((errnb = get_value(av, &p, sv)) != IS_OK)
				return (errnb);
		}
		else if (sv->port == NULL)
		{
			if (!only_positive_number(av[p.i]))
				return (ERR_DIGIT_PARAM);
			sv->port = av[p.i];
		}
		else
			return (ERR_TOOMUCH_PARAM);
		p.i++;
	}
	return ((!sv->port) ? ERR_NB_PARAMS : IS_OK);
}
