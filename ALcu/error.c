/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 00:10:04 by ggarrigu          #+#    #+#             */
/*   Updated: 2014/03/09 23:26:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int			ft_param_error(int ac, char **av)
{
	int		ret;
	char	*error[8];

	error[0] = "Line must be a number";
	error[1] = "Line must be a positive number";
	error[2] = "Line must be lower than 2147483648";
	error[3] = "Line must be upper to 5";
	error[4] = "Column must be a number";
	error[5] = "Column must be a positive number";
	error[6] = "Column must be lower than 2147483648";
	error[7] = "Column must be upper to 6";
	if (ac == 3 && (ret = ft_check_param(av[1], av[2])) >= 1 && ret <= 8)
	{
		ft_putendl("Usage : ./puissance4 line column");
		ft_putendl(error[ret - 1]);
		return (-1);
	}
	else if (ac != 3)
	{
		ft_putendl("Usage : ./puissance4 line column");
		return (-1);
	}
	return (0);
}
