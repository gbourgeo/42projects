// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stdlib_func.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 15:55:19 by root              #+#    #+#             //
//   Updated: 2017/11/11 22:37:06 by root             ###   ########.fr       //
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

const char *	mystrncpy(const char *dst, const char *src, int len)
{
	char		*dst2 = (char *)dst;
	char		*src2 = (char *)src;

	while (*src2 && len-- > 0)
		*dst2++ = *src2++;
	*dst2 = '\0';
	while (len-- > 0)
		*dst2++ = '\0';
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

char *			mystrchr(const char *s, char c)
{
	char		*p = (char *)s;

	if (!p)
		return (char *)0;
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

int				myisalnum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	if (c >= 'A' && c <= 'Z')
		return 1;
	if (c >= 'a' && c <= 'z')
		return 1;
	return 0;
}
