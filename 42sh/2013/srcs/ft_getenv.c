/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 15:37:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/06 18:48:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_getenv(char *search, char **env)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(search, env[i], ft_strlen(search)))
			return (env[i] + ft_strlen(search));
		i++;
	}
	return (NULL);
}
