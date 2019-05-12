/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getnenvaddr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 02:43:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 10:12:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

char			**sh_getnenvaddr(const char *name, char **env)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = (name) ? ft_strlen(name) : 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (sh_strncmp(env[i], name, len) == '=')
			return (env + i);
		i++;
	}
	return (NULL);
}
