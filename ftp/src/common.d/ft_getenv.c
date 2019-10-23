/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 09:55:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/23 18:09:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

char			*ft_getenv(char *search, char **envp)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(search);
	if (envp)
	{
		while (envp[i])
		{
			if (!ft_strncmp(search, envp[i], len))
				return (ft_strdup(envp[i] + len));
			i++;
		}
	}
	return (NULL);
}
