/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 00:10:04 by ggarrigu          #+#    #+#             */
/*   Updated: 2019/07/31 00:20:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int			ft_param_error(int ac, char **av)
{
	static char	*error[] = {
		"Try again.",
		"Line must be a number.",
		"Line must be a positive number.",
		"Line must be lower than 2147483648.",
		"Line must be upper to 5.",
		"Column must be a number.",
		"Column must be a positive number.",
		"Column must be lower than 2147483648.",
		"Column must be upper to 6.",
	};
	int			ret;

	ret = 0;
	if (ac != 3 || (ret = ft_check_param(av[1], av[2])))
	{
		ft_putendl("Usage : ./puissance4 [line] [column]");
		ft_putendl(error[ret]);
		return (1);
	}
	return (ret);
}
