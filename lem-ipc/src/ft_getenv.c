/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 12:12:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/30 04:59:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_getenv(char *str, char **env)
{
	int		i;

	i = 0;
	if (env && str)
	{
		while (env[i] != NULL)
		{
			if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			{
				if (env[i][ft_strlen(str)] == '=')
					return (env[i] + ft_strlen(str) + 1);
			}
			++i;
		}
	}
	return (NULL);
}
