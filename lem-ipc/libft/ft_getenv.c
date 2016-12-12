/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:45:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/10 13:56:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_getenv(char *var, char **env)
{
	int			i;
	int			j;

	i = 0;
	if (var == NULL || env == NULL)
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (var[j] && env[i][j] && var[j] == env[i][j])
			j++;
		if (!var[j] && env[i][j] == '=')
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}
