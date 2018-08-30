/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:02:59 by root              #+#    #+#             */
/*   Updated: 2018/08/30 02:34:46 by root             ###   ########.fr       */
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

static int		tab_lines(char *s)
{
	int			i;
	int			lines;

	i = 0;
	lines = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && (s[i] < 9 || s[i] > 11))
		{
			lines += 1;
			while (s[i] != ' ' && (s[i] < 9 || s[i] > 11) && s[i] != '\0')
				++i;
		}
		else
			++i;
	}
	return (lines);
}

static char		*fill_tab(char *str)
{
	int			i;
	char		*copy;

	i = 0;
	copy = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i] != ' ' && (str[i] < 9 || str[i] > 11) && str[i] != '\0')
		i += 1;
	if ((copy = (char*)malloc(sizeof(copy) * (i + 1))) == NULL)
		return (NULL);
	copy[i] = '\0';
	while (--i >= 0)
		copy[i] = str[i];
	return (copy);
}

char			**mysplitwhitespaces(char *str)
{
	int			i;
	int			j;
	char		**tab;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(*tab) * (tab_lines(str) + 1))) == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 11))
		{
			if ((tab[j++] = fill_tab(str + i)) == NULL)
				break ;
			while (str[i] != ' ' && (str[i] < 9 || str[i] > 11) && str[i])
				++i;
		}
		else
			++i;
	}
	tab[j] = NULL;
	return (tab);
}

void			mytabdel(char ***tab)
{
	char		**ptr;

	if (tab) {
		if (*tab) {
			ptr = *tab;
			while (*ptr)
				free(*ptr++);
			free(*tab);
			*tab = NULL;
		}
	}
}
