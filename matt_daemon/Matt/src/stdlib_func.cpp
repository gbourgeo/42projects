// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stdlib_func.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 15:55:19 by root              #+#    #+#             //
//   Updated: 2017/10/15 23:45:23 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

typedef unsigned long size_t;

const void *	mymemset(const void *s, int c, unsigned int n)
{
	char	*t = (char *)s;

	while (n--)
		*t++ = c;
	return s;
}

const char *	mystrcpy(const char *dst, const char *src)
{
	char		*dst2 = (char *)dst;
	char		*src2 = (char *)src;

	while (*src2)
		*dst2++ = *src2++;
	*dst2 = '\0';
	return dst;
}

const char *	mystrcat(const char *dst, const char *src)
{
	char		*dst2 = (char *)dst;
	char		*src2 = (char *)src;

	while (*dst2)
		dst2++;
	while (*src2)
		*dst2++ = *src2++;
	*dst2 = '\0';
	return dst;
}

size_t			mystrlen(const char *s)
{
	size_t		i = 0;

	while (s && s[i])
		i++;
	return i;
}

char *	mystrchr(const char *s, char c)
{
	char		*p = (char *)s;

	while (*p)
	{
		if (*p == c)
			return p;
		p++;
	}
	return (char *)0;
}

int				mystrcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return *s1 - *s2;
}
