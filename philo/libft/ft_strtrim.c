/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 20:09:08 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/25 20:09:13 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlentrim_before(const char *s)
{
	int		i;

	i = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		++s;
		++i;
	}
	return (i);
}

int		ft_strlentrim_after(const char *s)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen((char *)s) - 1;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
	{
		--j;
		++i;
	}
	return (i);
}

char	*ft_strtrim(char const *s)
{
	char	*new_s;
	char	*tmp;
	int		len;
	int		i;
	int		len_before;

	if (s == NULL)
		return (NULL);
	len_before = ft_strlentrim_before(s);
	len = ft_strlen((char *)s) - (len_before + ft_strlentrim_after(s));
	new_s = (char *)malloc(sizeof(char) * len + 1);
	if (new_s == NULL)
		return (NULL);
	tmp = new_s;
	i = len_before;
	while (len--)
	{
		*new_s = s[i];
		new_s++;
		i++;
	}
	*new_s = '\0';
	return (tmp);
}
