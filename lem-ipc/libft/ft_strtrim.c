/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 20:37:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/01 18:10:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	size_t		i;
	size_t		j;
	char		*s2;

	i = 0;
	if (s == NULL)
		return (NULL);
	j = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		++i;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && j)
		--j;
	if (j < i)
		s2 = ft_strnew(1);
	else if (i == 0 && j == i)
		s2 = ft_strdup(s);
	else
		s2 = ft_strsub(s, i, (j - i + 1));
	return (s2);
}
