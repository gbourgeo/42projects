/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:37:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 05:14:18 by gbourgeo         ###   ########.fr       */
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

static int		get_value(char *av, t_server *sv)
{
	if (ft_strequ(av + 1, "i"))
		sv->interactive = 1;
	else if (ft_strequ(av + 1, "v4"))
		sv->version = (1 << v4);
	else if (ft_strequ(av + 1, "v6"))
		sv->version = (1 << v6);
	else
		return (ERR_WRONG_PARAM);
	return (IS_OK);
}

int				sv_params(char **av, t_server *sv)
{
	int			i;

	i = 1;
	sv->version = (1 << v4) + (1 << v6);
	while (av[i])
	{
		if (av[i][0] == '-')
			get_value(av[i], sv);
		else if (sv->port == NULL)
		{
			if (!only_positive_number(av[i]))
				return (ERR_DIGIT_PARAM);
			sv->port = av[i];
		}
		else
			return (ERR_TOOMUCH_PARAM);
		i++;
	}
	return ((!sv->port) ? ERR_NB_PARAMS : IS_OK);
}
