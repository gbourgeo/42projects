/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:07:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/21 00:47:44 by gbourgeo         ###   ########.fr       */
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
		return (1);
	ft_strncpy(new, *command, i);
	ft_strcpy(new + i, ptr);
	ft_strcat(new, *command + i + 2);
	free(ptr);
	free(*command);
	*command = new;
	return (len);
}

static int		ft_dollar_copy(char c, int cmdlen, size_t i, t_env *e)
{
	char		*ptr;
	char		*new;
	int			len;

	ptr = ft_getenv((const char *)(e->command + i + 1), e->env);
	len = cmdlen - ft_strlen(e->command + i) + ft_strlen(ptr);
	if ((new = ft_strnew(len)) == NULL)
		return (1);
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
	return (ft_strlen(ptr));
}

int				ft_dollar(size_t i, t_env *e)
{
	char		*ptr;
	int			len;
	char		c;

	ptr = e->command + i + 1;
	len = ft_strlen(e->command);
	if (!*ptr)
		return (1);
	if (*ptr == '$')
		return (ft_dollar_getint(&e->command, i, getpid()));
	if (*ptr == '?')
		return (ft_dollar_getint(&e->command, i, e->ret));
	while (*ptr && *ptr != '\t' && *ptr != ' ' && *ptr != '$')
		ptr++;
	c = *ptr;
	*ptr = '\0';
	return (ft_dollar_copy(c, len, i, e));
}

int				ft_tilde(size_t i, t_env *e)
{
	char		*new;
	char		*ptr;
	int			len;

	ptr = e->command + i;
	if ((!i || *(ptr - 1) == ' ' || *(ptr - 1) == '\t')
		&& (*(ptr + 1) == '\0' || *(ptr + 1) == ' ' || *(ptr + 1) == '\t'
			|| *(ptr + 1) == '/'))
	{
		ptr = ft_getenv("HOME", e->env);
		len = ft_strlen(e->command) + ft_strlen(ptr);
		if ((new = malloc(len)) == NULL)
			return (1);
		ft_strncpy(new, e->command, i);
		ft_strcpy(new + i, ft_getenv("HOME", e->env));
		ft_strcat(new, e->command + i + 1);
		free(e->command);
		e->command = new;
		return (ft_strlen(ptr));
	}
	return (1);
}
