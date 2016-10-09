/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 15:55:31 by root              #+#    #+#             */
/*   Updated: 2016/10/10 00:23:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfts.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define NAMES  "bzero", "strcat", "isalpha", "isdigit", "isalnum", \
		"isascii", "isprint", "toupper", "tolower", "puts", \
		"strlen", "memset", "memcpy", "strdup", "cat", \
		"memchr", "memrchr", "memcmp", NULL

# define FUNCTIONS  test1, test2, test3, test4, test5, \
		test6, test7, test8, test9, test10, \
		test11, test12, test13, test14, test15, \
		test16, test17, test18, NULL

static void	check_it(int i)
{
	if (i)
	{
		write(1, "\ntest FAILED\n", 15);
		exit(i);
	}
	write(1, "\ntest OK", 8);
}

static void test1(void)
{
	char	str[10] = "coucou";

	printf("\033[31m\n**** TEST FT_BZERO ****\033[0m\n");
	write(1, "str: ", 5);
	write(1, str, 6);
	write(1, "\n", 1);
	write(1, "bzero: ", 7);
	_ft_bzero(str, 6);
	write(1, str, 6);
	check_it(*str);
}
static void test2(void)
{
	char	cat[30] = "je suis";
	char	plus[30] = " le plus beau";

	printf("\033[31m\n**** TEST FT_STRCAT ****\033[0m\n");
	write(1, "str: ", 5);
	write(1, cat, 30);
	write(1, "\n", 1);
	write(1, "strcat: ", 8);
	_ft_strcat(cat, plus);
	write(1, cat, 30);
	check_it(strlen(cat) < 20);
}
static void test3(void)
{
	int	i = ' ';

	printf("\033[31m");
	write(1, "\n\n**** TEST FT_ISALPHA ****\n", 27);
	printf("\033[0m");
	while (i < 127)
	{
		write(1, &i, 1);
		if (_ft_isalpha(i))
			write(1, " is alpha", 9);
		else
			write(1, " isn't alpha", 12);
		i++;
		if (i % 4 == 0)
			write (1, "\n", 1);
		else
			write(1, "\t", 1);
	}
	write (1, "\n", 1);
}
static void test4(void)
{
	int i = ' ';

	printf("\033[31m\n**** TEST FT_ISDIGIT ****\033[0m\n");
	while (i < 127)
	{
		write(1, &i, 1);
		if (_ft_isdigit(i))
			write(1, " is digit", 9);
		else
			write(1, " isn't digit", 12);
		i++;
		if (i % 4 == 0)
			write (1, "\n", 1);
		else
			write(1, "\t", 1);
	}
	write (1, "\n", 1);
}
static void test5(void)
{
	int i = ' ';

	printf("\033[31m\n**** TEST FT_ISALNUM ****\033[0m\n");
	while (i < 127)
	{
		write(1, &i, 1);
		if (_ft_isalnum(i))
			write(1, " is alnum", 9);
		else
			write(1, " isn't alnum", 12);
		i++;
		if (i % 4 == 0)
			write (1, "\n", 1);
		else
			write(1, "\t", 1);
	}
	write (1, "\n", 1);
}
static void test6(void)
{
	int i = -10;

	printf("\033[31m\n**** TEST FT_ISASCII ****\033[0m\n");
	while (i < 130)
	{
		write(1, &i, 1);
		if (_ft_isascii(i))
			write(1, " is ascii", 9);
		else
			write(1, " isn't ascii", 12);
		i++;
		if (i % 4 == 0)
			write (1, "\n", 1);
		else
			write(1, "\t", 1);
	}
	write (1, "\n", 1);
}
static void test7(void)
{
	int i = 0;

	printf("\033[31m\n**** TEST FT_ISPRINT ****\033[0m\n");
	while (i < 128)
	{
		write(1, &i, 1);
		if (_ft_isprint(i))
			write(1, " is print", 9);
		else
			write(1, " isn't print", 12);
		i++;
		if (i % 4 == 0)
			write (1, "\n", 1);
		else
			write(1, "\t", 1);
	}
	write (1, "\n", 1);
}
static void test8(void)
{
	char	str[40] = "Bonjour monsieur/madame -'\"() ok !";
	int i = 0;

	printf("\033[31m\n**** TEST FT_TOUPPER ****\033[0m\n");
	printf("str is '%s'\n", str);
	while (str[i]) {
		str[i] = _ft_toupper(str[i]);
		i++; }
	printf("all toupper -> %s\n", str);
}
static void test9(void)
{
	char	str[40] = "HEY HO SALUT -'\"() DUDE DONE !";
	int i = 0;

	printf("\033[31m\n**** TEST FT_TOLOWER ****\033[0m\n");
	printf("str is '%s'\n", str);
	while (str[i]) {
		str[i] = _ft_tolower(str[i]);
		i++; }
	printf("all tolower -> %s\n", str);
}
static void test10(void)
{
	int i, j;
	char test[10] = "";

	printf("\033[31m\n**** TEST FT_PUTS ****\033[0m\n");
	i = _ft_puts("ft: All of this text");
	printf("ft_puts=%d puts=%d\n", i, puts("  : All of this text"));
	i = _ft_puts("ft: have been written by the function ft_puts()");
	printf("ret=%d real=%d\n", i, puts("  : have been written by the function ft_puts()"));
	i = _ft_puts("ft: from gbourgeo.");
	printf("ret=%d real=%d\n", i, puts("  : from gbourgeo."));
	i = _ft_puts("ft: Give him all the points ;)");
	printf("ret=%d real=%d\n", i, puts("  : Give him all the points ;)"));
	i = _ft_puts(test);
	printf("ret=%d real=%d\n", i, puts(test));
}
static void test11(void)
{
	int i, j;

	printf("\033[31m\n**** TEST FT_STRLEN ****\033[0m\n");
	printf("'%s' : ret=%d \t real=%d\n", "aaaa", _ft_strlen("aaaa"), strlen("aaaa"));
	printf("'%s' : ret=%d \t real=%d\n", "", _ft_strlen(""), strlen(""));
	printf("'%s' : ret=%d \t real=%d\n", "zqfesxdcfhbjncds eiuhg efug",
		   _ft_strlen("zqfesxdcfhbjncds eiuhg efug"), strlen("zqfesxdcfhbjncds eiuhg efug"));
}

static void	test12(void)
{
	char	test[50];
	char	test2[50];

	printf("\033[31m\n**** TEST FT_MEMSET ****\033[0m\n");
	printf("ft_memset: %s\n", _ft_memset(NULL, 0, 30));
	_ft_memset(test, 'a', 30);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'a', 30));
	_ft_memset(test, 'b', 25);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'b', 25));
	_ft_memset(test, 'c', 20);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'c', 20));
	_ft_memset(test, 'd', 15);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'd', 15));
	_ft_memset(test, 'e', 10);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'e', 10));
	_ft_memset(test, 'f', 5);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'f', 5));
	_ft_memset(test, 'g', 0);
	printf("ft_memset: %s \t memset: %s\n", test, memset(test2, 'g', 0));	
}
static void	test13(void)
{
	char	test[50];
	char	test2[50];

	printf("\033[31m\n**** TEST FT_MEMCPY ****\033[0m\n");
	memset(test, 0, 50);
	memset(test2, 0, 50);
	memcpy(test2, "bonjour", 7);
	_ft_memcpy(test, test2, 7);
	printf("ft_memcpy: %s\n", test);
	memcpy(test2, "bonjour", 7);
	_ft_memcpy(NULL, test2, 8);
	printf("ft_memcpy: %s (dest NULL)\n", test);
	memcpy(test2, "bonjour", 7);
	_ft_memcpy(test, NULL, 7);
	printf("ft_memcpy: %s (source NULL)\n", test);
	memcpy(test2, "bonjour", 50);
	_ft_memcpy(test, test2, 0);
	printf("ft_memcpy: %s (size = 0)\n", test);
	memcpy(test2, "comment ca va ?", 7);
	_ft_memcpy(test, test2, 7);
	printf("ft_memcpy: %s (copy 7 bits de 'comment ca va ?')\n", test);
	memcpy(test2, "comment ca va ?", 50);
	_ft_memcpy(test, test2, 50);
	printf("ft_memcpy: %s (copy 50 bits de 'comment ca va ?')\n", test);
}
static void	test14(void)
{
	char	src[50];
	char	*dst;
	char	*tst = "";

	dst = NULL;
	printf("\033[31m\n**** TEST FT_STRDUP ****\033[0m\n");
	memcpy(src, "ft_strdup marche a merveille", 50);
	dst = _ft_strdup(src);
	if (dst)
	{
		printf("ft_strdup de '%s' give -> '%s'\n", src, dst);
		free(dst);
		dst = NULL;
	}
	else
		printf("ft_strdup :(. ERROR\n");
	dst = _ft_strdup(tst);
	if (dst)
	{
		printf("ft_strdup de '%s' give -> '%s'\n", tst, dst);
		free(dst);
		dst = NULL;
	}
	else
		printf("ft_strdup :(. ERROR\n");
}
static void test15(void)
{
	int fd;

	printf("\033[31m\n**** TEST FT_CAT ****\033[0m\n");
	printf("\033[32mtest with a fd < 0...\033[0m");
	_ft_cat(-1);
	printf(" OK\n");
	fd = open("auteur", O_RDONLY);
	printf("\033[32mtest on 'auteur' (fd=%d)...\033[0m\n", fd);
	_ft_cat(fd);
	close(fd);
	fd = open("Makefile", O_RDONLY);
	printf("\033[32mtest on 'Makefile' (fd=%d)...\033[0m\n", fd);
	_ft_cat(fd);
	close(fd);
	fd = 0;
	printf("\033[32mtest on fd = 0...\033[0m\n", fd);
	_ft_cat(fd);
}

static void test16(void)
{
	char str[50] = "yolo swag poulet !";
	char *ret;
	int	i;

	printf("\033[31m\n**** TEST FT_MEMCHR ****\033[0m\n");
	i = 'l';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 50);
	printf("result: '%s'\nmemchr: '%s'\n", ret, memchr(str, i, 50));
	i = 's';
	printf("\033[32mRecherche '%c' dans '%s' (5 premiers caracteres)\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 5);
	printf("result: '%s'\nmemchr: '%s'\n", ret, memchr(str, i, 5));
	printf("\033[32mRecherche '%c' dans '%s' (15 premiers caracteres)\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 15);
	printf("result: '%s'\nmemchr: '%s'\n", ret, memchr(str, i, 15));
	i = 'F';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 50);
	printf("result: '%s'\nmemchr: '%s'\n", ret, memchr(str, i, 50));
	i = 0;
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 50);
	printf("result: '%s'\nmemchr: '%s'\n", ret, memchr(str, i, 50));
}
static void test17(void)
{
	char str[50] = "yolo swag poulet !";
	int	i;

	str[18] = '\0';
	printf("\033[31m\n**** TEST FT_MEMRCHR ****\033[0m\n");
	i = 'l';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", _ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
	printf("\033[32mRecherche '%c' dans '%s' (en Commencant a 10)\033[0m\n", i, str);
	printf("result: '%s'\n", _ft_memrchr(str, i, 10));//, memrchr(str, i, 50));
	i = 'o';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", _ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
	printf("\033[32mRecherche '%c' dans '%s' (en Commencant a 5)\033[0m\n", i, str);
	printf("result: '%s'\n", _ft_memrchr(str, i, 5));//, memrchr(str, i, 5));
	i = 'F';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", _ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
	i = 0;
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", _ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
}
static void test18(void)
{
	char str[50] = "comment ca va bien ? ca va ?";
	char ste[50] = "comment ca va bien ?";
	char stt[50] = "salut ca va et toi ?";
	int i;

	printf("\033[31m\n**** TEST FT_MEMCMP ****\033[0m\n");
	printf("str1 is '%s'\nstr2 is '%s'\n", str, ste);
	i = 50;
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(str, ste, i));
	printf("memcmp: %d\n", memcmp(str, ste, i));
	i = 20;
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(str, ste, i));
	printf("memcmp: %d\n", memcmp(str, ste, i));
	i = 21;
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(str, ste, i));
	printf("memcmp: %d\n", memcmp(str, ste, i));
	i = -1;
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(str, ste, i));
	printf("memcmp: %d\n", memcmp(str, ste, i));

	i = 50;
	printf("\nstr2 is '%s'\nstr3 is '%s'\n", ste, stt);
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(ste, stt, i));
	printf("memcmp: %d\n", memcmp(ste, stt, i));
	ste[0] = 'm';
	printf("\nstr2 is '%s'\nstr3 is '%s'\n", ste, stt);
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(ste, stt, i));
	printf("memcmp: %d\n", memcmp(ste, stt, i));
	ste[0] = 'r';
	printf("\nstr2 is '%s'\nstr3 is '%s'\n", ste, stt);
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(ste, stt, i));
	printf("memcmp: %d\n", memcmp(ste, stt, i));
	ste[0] = 'z';
	printf("\nstr2 is '%s'\nstr3 is '%s'\n", ste, stt);
	printf("\e[32mComparaison des 2 strings d'une longueur de %d\e[0m\n", i);
	printf("ft_mem: %d\n", _ft_memcmp(ste, stt, i));
	printf("memcmp: %d\n", memcmp(ste, stt, i));
}
static void	get_opt(char **av)
{
	static char	*name[] = { NAMES };
	static void	(*fct[])(void) = { FUNCTIONS };
	char	buf[6];
	int		i = 1, j;

	while (av[i])
	{
		j = 0;
		while (name[j])
		{
			if (strcmp(av[i], name[j]) == 0)
			{
				fct[j]();
				write(0, "\nDONE\nPress any key to continue", 31);
//				read(0, buf, 5);
				break ;
			}
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int		opt = 0;
	char	*name[] = { NAMES };

	if (ac == 1)
		get_opt(name);
	else
		get_opt(av);
	write(1, "End.\n", 5);
	return (0);
}
