/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:48:46 by root              #+#    #+#             */
/*   Updated: 2018/07/12 13:52:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				dollar_expansion(char **command, size_t i, char **env)
{
	char		*new;
	char		*ptr;
	char		*getenv;
	char		c[2];
	int			len;

	c[1] = '\0';
	ptr = command;
	if (ft_isdigit(*(ptr + 1)))
		return (i);
	if ((new = ft_strchr(ptr + 1, ' ')) != NULL ||
		((new = ft_strchr(ptr + 1, '\t')) != NULL) ||
		((new = ft_strchr(ptr + 1, '\n')) != NULL) ||
		((new = ft_strchr(ptr + 1, '\v')) != NULL) ||
		((new = ft_strchr(ptr + 1, '$')) != NULL) ||
		((new = ft_strchr(ptr + 1, '\0')) != NULL))
		*c = *new;
	len = ft_strlen(command) - (int)(new - ptr);
	*new = '\0';
	getenv = ft_getenv(ptr + 1, env);
	len += ft_strlen(getenv);
	*ptr = '\0';
	ptr = new;
	if ((new = malloc(len)) == NULL)
		return (i);
	ft_strcpy(new, command);
	ft_strcat(new, getenv);
	ft_strcat(new, c);
	if (*c)
		ft_strcat(new, ptr + 1);
	free(command);
	command = new;
	return (i);
}
