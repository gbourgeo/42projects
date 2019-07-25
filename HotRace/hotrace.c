/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 22:21:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:57:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void		initialize_vars(char **k, char **v, t_tree **t)
{
	*k = NULL;
	*v = NULL;
	*t = NULL;
}

int				main(void)
{
	char	*keyword;
	char	*value;
	t_tree	*tab;

	initialize_vars(&keyword, &value, &tab);
	while ((get_next_line(0, &keyword)) == 1 && *keyword)
	{
		if ((get_next_line(0, &value)) != 1)
			return (0);
		ft_add_node(tab, keyword, value);
	}
	while ((get_next_line(0, &keyword)) == 1 && *keyword)
	{
		if ((ft_search_node(tab, keyword)) == 1)
			return (-1);
		free(keyword);
	}
	return (0);
}
