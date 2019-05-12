/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getnenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 18:44:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 18:59:22 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

char			*sh_getnenv(const char *name, char **env)
{
	size_t		i;
	size_t		len;

	i = 0;
	if (!env || !name)
		return (NULL);
	len = ft_strlen(name) + 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == '=')
			return (&env[i][len]);
		i++;
	}
	return (NULL);
}
