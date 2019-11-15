/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:37:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 14:37:48 by gbourgeo         ###   ########.fr       */
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

static int		get_value(char **av, int *i, t_server *sv)
{
	int			j;

	j = 0;
	while (av[*i][++j])
		if (av[*i][j] == 'i')
			sv->options |= (1 << sv_interactive);
		else if (av[*i][j] == '4')
		{
			sv->options |= (1 << sv_v4);
			sv->options &= ~(1 << sv_v6);
		}
		else if (av[*i][j] == '6')
		{
			sv->options |= (1 << sv_v6);
			sv->options &= ~(1 << sv_v4);
		}
		else if (av[*i][j] == 'd')
			sv->options |= (1 << sv_create_dir);
		else if (av[*i][j] == 'p')
			return (sv_param_p_get(av[++(*i)], sv));
		else if (av[*i][j] == 'h' || ft_strequ(&av[*i][j], "-help"))
			return (ERR_HELP);
		else
			return (ERR_WRONG_PARAM);
	return (IS_OK);
}

int				sv_params_get(char **av, t_server *sv)
{
	int			i;
	int			errnb;

	i = 1;
	sv->options |= ((1 << sv_v4) | (1 << sv_v6));
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if ((errnb = get_value(av, &i, sv)) != IS_OK)
				return (errnb);
		}
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
