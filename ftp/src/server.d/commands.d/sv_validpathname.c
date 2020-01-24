/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_validpathname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:50:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/21 18:54:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_validpathname(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		if (s[i] < 0 || s[i] == '\r' || s[i] == '\n')
			return (0);
		else
			i++;
	return (i != 0);
}
