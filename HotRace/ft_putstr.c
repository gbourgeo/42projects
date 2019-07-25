/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 20:56:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 22:46:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int		ft_strlen(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void			ft_putstr(char const *str)
{
	write(1, str, ft_strlen(str));
}
