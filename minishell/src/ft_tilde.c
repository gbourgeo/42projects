/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 09:18:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/26 09:28:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_tilde_getenv(size_t i, size_t j, const char *var, t_env *e)
{
	char		*new;
	char		*ptr;
	int			len;

	ptr = ft_getenv(var, e->env);
	len = ft_strlen(e->command) + ft_strlen(ptr);
	if ((new = malloc(len)) == NULL)
		return (1);
	ft_strncpy(new, e->command, i);
	ft_strcpy(new + i, ft_getenv(var, e->env));
	ft_strcat(new, e->command + i + j);
	free(e->command);
	e->command = new;
	return (ft_strlen(ptr));
}

int				ft_tilde(size_t i, t_env *e)
{
	char		*ptr;

	ptr = e->command + i;
	if ((!i || *(ptr - 1) == ' ' || *(ptr - 1) == '\t'))
	{
		if ((*(ptr + 1) == '\0' || *(ptr + 1) == ' ' || *(ptr + 1) == '\t'
			|| *(ptr + 1) == '/'))
			return (ft_tilde_getenv(i, 1, "HOME", e));
		if (*(ptr + 1) == '+')
			return (ft_tilde_getenv(i, 2, "PWD", e));			
		if (*(ptr + 1) == '-')
			return (ft_tilde_getenv(i, 2, "OLDPWD", e));
	}
	return (1);
}
