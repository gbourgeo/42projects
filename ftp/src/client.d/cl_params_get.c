/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_params_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:36:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/11 16:41:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include "cl_struct.h"

static int		only_digit(const char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

static int		get_value(char **av, t_param *p, t_client *cl)
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
				if ((errnb = p->opts[k].function(av, &p->i, cl)) != IS_OK)
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

static void		init_param(t_param *p, t_client *cl)
{
	p->opts = cl_params(0);
	p->size = (size_t)cl_params(1);
	p->i = 1;
	cl->options = 0;
	cl->port = NULL;
	cl->addr = NULL;
}

int				cl_params_get(char **av, t_client *cl)
{
	t_param		p;
	int			errnb;

	init_param(&p, cl);
	errnb = IS_OK;
	while (av[p.i])
	{
		if (av[p.i][0] == '-')
		{
			if ((errnb = get_value(av, &p, cl)) != IS_OK)
				return (errnb);
		}
		else if (cl->addr == NULL)
			cl->addr = av[p.i];
		else if (cl->port == NULL)
		{
			if (!only_digit(av[p.i]))
				return (ERR_DIGIT_PARAM);
			cl->port = av[p.i];
		}
		else
			return (ERR_TOOMUCH_PARAM);
		p.i++;
	}
	return ((!cl->port || !cl->addr) ? ERR_NB_PARAMS : IS_OK);
}
