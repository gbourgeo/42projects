/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 06:39:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/05 07:18:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	table_length(char *str, char c)
{
	size_t		len;

	len = 0;
	while (*str)
	{
		while (*str && *str != c)
			str++;
		len++;
		if (*str)
			str++;
	}
	return (len + 1);
}

static size_t	line_length(char *str, char c)
{
	size_t		len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len + 1);
}

char			**sv_strsplit(char *str, char c)
{
	char		**ret;
	size_t		i;
	size_t		j;

	i = 0;
	if (!str || !(ret = malloc(sizeof(*ret) * table_length(str, c))))
		return (NULL);
	while (*str)
	{
		if (!(ret[i] = malloc(sizeof(**ret) * line_length(str, c))))
			return (ret);
		j = 0;
		while (*str && *str != c)
			ret[i][j++] = *str++;
		if (*str)
			str++;
		ret[i++][j] = '\0';
	}
	ret[i] = NULL;
	return (ret);
}
