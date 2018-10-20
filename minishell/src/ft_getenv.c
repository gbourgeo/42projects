/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 12:12:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 15:49:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_getenv(const char *str, const char **env)
{
	int		i;

	i = 0;
	if (env && str)
	{
		while (env[i])
		{
			if (ft_strcmp(env[i], str) == '=')
				return (char *)(env[i] + ft_strlen(str) + 1);
			++i;
		}
	}
	return (NULL);
}

char		**ft_getenvaddr(const char *str, const char **env)
{
	int		i;

	i = 0;
	if (env && str)
	{
		while (env[i] != NULL)
		{
			if (ft_strcmp(env[i], str) == '=')
					return (char **)(&env[i]);
			++i;
		}
	}
	return (NULL);
}
