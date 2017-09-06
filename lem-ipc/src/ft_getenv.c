/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:41:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/06 20:41:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
