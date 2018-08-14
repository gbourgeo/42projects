/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:02:59 by root              #+#    #+#             */
/*   Updated: 2018/08/14 00:41:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* malloc */
#include <stdlib.h>

int				mystrlen(const char *s1)
{
	char	*p = (char *)s1;

	if (!p)
		return (0);
	while (*p)
		p++;
	return (p-s1);
}

void			*mymemset(void *s, int c, unsigned int n)
{
	unsigned char	*p = (unsigned char *)s;

	while (n--)
		*p++ = c;
	return (s);
}

int				mystrcmp(const char *s1, const char *s2)
{
	int		i = 0;

	if (!s1 || !s2)
		return (-1);
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char			*myitoa(int n)
{
	char	*p;
	int		sign;
	int		i;
	int		src;

	src = n;
	i = (n < 0 ? 3 : 2);
	while ((n /= 10))
		++i;
	if ((p = (char*)malloc(sizeof(*p) * i)) == NULL)
		return (NULL);
	p[--i] = '\0';
	if (src == 0)
		p[0] = '0';
	if ((sign = (src < 0 ? -1 : 1)) < 0)
		p[0] = '-';
	while (src != 0)
	{
		p[--i] = ((src % 10) * sign + 48);
		src /= 10;
	}
	return (p);
}
