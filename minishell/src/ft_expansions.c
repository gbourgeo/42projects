/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:48:46 by root              #+#    #+#             */
/*   Updated: 2018/10/20 17:36:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_dollar_getint(char **command, size_t i, int value)
{
	char		*ptr;
	char		*new;
	int			len;

	ptr = ft_itoa(value);
	len = ft_strlen(ptr);
	new = ft_strnew(ft_strlen(*command) + len);
	if (new == NULL)
		return (i);
	ft_strncpy(new, *command, i);
	ft_strcpy(new + i, ptr);
	ft_strcat(new, *command + i + 2);
	free(ptr);
	free(*command);
	*command = new;
	return (i + len);
}

int				ft_dollar(size_t i, t_env *e)
{
	char		*new;
	char		*ptr;
	int			len;
	char		c;

	ptr = e->command + i + 1;
	len = ft_strlen(e->command);
	if (!*ptr)
		return (i);
	if (*ptr == '$')
		return (ft_dollar_getint(&e->command, i, getpid()));
	if (*ptr == '?')
		return (ft_dollar_getint(&e->command, i, e->ret));
	while (*ptr && *ptr != '\t' && *ptr != ' ')
		ptr++;
	c = *ptr;
	*ptr = '\0';
	ptr = ft_getenv((const char *)(e->command + i + 1), e->env);
	len = len - ft_strlen(e->command + i) + ft_strlen(ptr);
	if ((new = ft_strnew(len)) == NULL)
		return (i);
	ft_strncpy(new, e->command, i);
	ft_strcpy(new + i, ptr);
	if (c)
	{
		len = ft_strlen(new);
		*(new + len) = c;
		ft_strcpy(new + len + 1, e->command + ft_strlen(e->command) + 1);
	}
	free(e->command);
	e->command = new;
	return (i + ft_strlen(ptr));
}

int				ft_tilde(size_t i, t_env *e)
{
	char		*new;
	char		*ptr;
	int			len;

	ptr = e->command + i;
	if ((*(ptr + 1) != '\0' && *(ptr + 1) != '/')
		|| (i && (*(ptr - 1) != '\t' && *(ptr - 1) != ' ')))
		return (i);
	ptr = ft_getenv("HOME", e->env);
	len = ft_strlen(e->command) + ft_strlen(ptr);
	if ((new = malloc(len)) == NULL)
		return (i);
	ft_strncpy(new, e->command, i);
	ft_strcpy(new + i, ft_getenv("HOME", e->env));
	ft_strcat(new, e->command + i + 1);
	free(e->command);
	e->command = new;
	return (i + ft_strlen(ptr));
}
