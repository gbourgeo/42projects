/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:02:59 by root              #+#    #+#             */
/*   Updated: 2018/08/09 15:27:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			mystrlen(const char *s1)
{
	char	*p = (char *)s1;

	if (!p)
		return (0);
	while (*p)
		p++;
	return (p-s1);
}

void		*mymemset(void *s, int c, unsigned int n)
{
	unsigned char	*p = (unsigned char *)s;

	while (n--)
		*p++ = c;
	return (s);
}

int			mystrcmp(const char *s1, const char *s2)
{
	int		i = 0;

	if (!s1 || !s2)
		return (-1);
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
