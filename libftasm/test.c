/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 15:55:31 by root              #+#    #+#             */
/*   Updated: 2016/10/13 18:31:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfts.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

# define NAMES  "bzero", "strcat", "isalpha", "isdigit", "isalnum", \
		"isascii", "isprint", "toupper", "tolower", "puts", \
		"strlen", "memset", "memcpy", "strdup", "cat", \
		"memchr", "memrchr", "memcmp", "putnbr", "iter", NULL

# define FUNCTIONS  test1, test2, test3, test4, test5, \
		test6, test7, test8, test9, test10, \
		test11, test12, test13, test14, test15, \
		test16, test17, test18, test19, test20, NULL

static void	check_it(int i)
{
	if (i)
	{
		printf("\ntest FAILED\n");
		exit(i);
	}
	printf("\ntest OK");
}

static void test1(void)
{
	char	str[10] = "coucou";

	printf("\033[31m\n**** TEST FT_BZERO ****\033[0m\n");
	printf("str: %s\nbzero: ", str);
	_ft_bzero(str, 6);
	printf("%s", str);
	check_it(*str);
}
static void test2(void)
{
	char	cat[30] = "je suis";
	char	plus[30] = " le plus beau";

	printf("\033[31m\n**** TEST FT_STRCAT ****\033[0m\n");
	printf("str: %s\nstrcat: ", cat);
	_ft_strcat(cat, plus);
	printf("%s", cat);
	check_it(strlen(cat) < 20);
}
static void test3(void)
{
	int	i = -127;

	printf("\033[31m\n**** TEST FT_ISALPHA ****\n\033[0m");
	while (i < 127)
	{
		if (_ft_isalpha(i) != isalpha(i))
		{
			printf("ERROR: %d != %d\n", _ft_isalpha(i), isalpha(i));
			exit(1);
		}
		i++;
	}
	printf("TEST OK !\n");
}
static void test4(void)
{
	int i = -128;

	printf("\033[31m\n**** TEST FT_ISDIGIT ****\033[0m\n");
	while (i < 127)
	{
		if (_ft_isdigit(i) != isdigit(i))
		{
			printf("ERROR: %d != %d\n", _ft_isdigit(i), isdigit(i));
			exit(1);
		}
		i++;
	}
	printf("TEST OK !\n");
}
static void test5(void)
{
	int i = -128;

	printf("\033[31m\n**** TEST FT_ISALNUM ****\033[0m\n");
	while (i < 127)
	{
		if (_ft_isalnum(i) != isalnum(i))
		{
			printf("ERROR: %d != %d\n", _ft_isalnum(i), isalnum(i));
			exit(1);
		}
		i++;
	}
	printf("TEST OK !\n");
}
static void test6(void)
{
	int i = -128;

	printf("\033[31m\n**** TEST FT_ISASCII ****\033[0m\n");
	while (i < 130)
	{
		if (_ft_isascii(i) != isascii(i))
		{
			printf("ERROR: %d != %d\n", _ft_isascii(i), isascii(i));
			exit(1);
		}
		i++;
	}
	printf("TEST OK !\n");
}
static void test7(void)
{
	int i = 0;

	printf("\033[31m\n**** TEST FT_ISPRINT ****\033[0m\n");
	while (i < 128)
	{
		if (_ft_isprint(i) != isprint(i))
		{
			printf("ERROR: %d != %d\n", _ft_isprint(i), isprint(i));
			exit(1);
		}
		i++;
	}
	printf("TEST OK !\n");
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
	int i;
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
	printf("\033[31m\n**** TEST FT_STRLEN ****\033[0m\n");
	printf("'%s' : ret=%d \t real=%ld\n", "aaaa", _ft_strlen("aaaa"), strlen("aaaa"));
	printf("'%s' : ret=%d \t real=%ld\n", "", _ft_strlen(""), strlen(""));
	printf("'%s' : ret=%d \t real=%ld\n", "zqfesxdcfhbjncds eiuhg efug",
		   _ft_strlen("zqfesxdcfhbjncds eiuhg efug"), strlen("zqfesxdcfhbjncds eiuhg efug"));
}

static void	test12(void)
{
	char	test[50];
	char	test2[50];

	printf("\033[31m\n**** TEST FT_MEMSET ****\033[0m\n");
	printf("ft_memset: %s\n", (char *)_ft_memset(NULL, 0, 30));
	_ft_memset(test, 'a', 30);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'a', 30));
	_ft_memset(test, 'b', 25);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'b', 25));
	_ft_memset(test, 'c', 20);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'c', 20));
	_ft_memset(test, 'd', 15);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'd', 15));
	_ft_memset(test, 'e', 10);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'e', 10));
	_ft_memset(test, 'f', 5);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'f', 5));
	_ft_memset(test, 'g', 1);
	printf("ft_memset: %s \t memset: %s\n", test, (char *)memset(test2, 'g', 1));
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
	fflush(stdout);
	_ft_cat(-42);
	printf(" OK\n");
	fd = open("auteur", O_RDONLY);
	printf("\033[32mtest on 'auteur' (fd=%d)\033[0m\n", fd);
	_ft_cat(fd);
	close(fd);
	fd = open("Makefile", O_RDONLY);
	printf("\033[32mtest on 'Makefile' (fd=%d)...\033[0m\n", fd);
	_ft_cat(fd);
	close(fd);
	fd = 0;
	printf("\033[32mtest on fd = 0...\033[0m\n");
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
	printf("result: '%s'\nmemchr: '%s'\n", ret, (char *)memchr(str, i, 50));
	i = 's';
	printf("\033[32mRecherche '%c' dans '%s' (5 premiers caracteres)\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 5);
	printf("result: '%s'\nmemchr: '%s'\n", ret, (char *)memchr(str, i, 5));
	printf("\033[32mRecherche '%c' dans '%s' (15 premiers caracteres)\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 15);
	printf("result: '%s'\nmemchr: '%s'\n", ret, (char *)memchr(str, i, 15));
	i = 'F';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 50);
	printf("result: '%s'\nmemchr: '%s'\n", ret, (char *)memchr(str, i, 50));
	i = 0;
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	ret = _ft_memchr(str, i, 50);
	printf("result: '%s'\nmemchr: '%s'\n", ret, (char *)memchr(str, i, 50));
}
static void test17(void)
{
	char str[50] = "yolo swag poulet !";
	int	i;

	str[18] = '\0';
	printf("\033[31m\n**** TEST FT_MEMRCHR ****\033[0m\n");
	i = 'l';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", (char *)_ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
	printf("\033[32mRecherche '%c' dans '%s' (en Commencant a 10)\033[0m\n", i, str);
	printf("result: '%s'\n", (char *)_ft_memrchr(str, i, 10));//, memrchr(str, i, 50));
	i = 'o';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", (char *)_ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
	printf("\033[32mRecherche '%c' dans '%s' (en Commencant a 5)\033[0m\n", i, str);
	printf("result: '%s'\n", (char *)_ft_memrchr(str, i, 5));//, memrchr(str, i, 5));
	i = 'F';
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", (char *)_ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
	i = 0;
	printf("\033[32mRecherche '%c' dans '%s'\033[0m\n", i, str);
	printf("result: '%s'\n", (char *)_ft_memrchr(str, i, 50));//, memrchr(str, i, 50));
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
	i = 22;
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
static void test19(void)
{
	printf("\033[31m\n**** TEST FT_PUTNBR ****\033[0m\n");
	_ft_putnbr(-35);
	printf("\n");
	_ft_putnbr(-1);
	printf("\n");
	_ft_putnbr(0);
	printf("\n");
	_ft_putnbr(1);
	printf("\n");
	_ft_putnbr(1078);
	printf("\n");
	_ft_putnbr(INT_MIN);
	printf("\n");
	_ft_putnbr(INT_MAX);
	printf("\n");
}
static void test_iter(char *s)
{
	if (*s >= 'a' && *s <= 'z')
		*s -= 32;
}
static void test_iter2(char *s)
{
	if (*s >= 'A' && *s <= 'Z')
		*s += 32;
}
static void test20(void)
{
	char	tst[50] = "hello my name is Kwame !";

	printf("\033[31m\n**** TEST FT_ITER ****\033[0m\n");
	printf("ft_iter(%s, %s): test_iter is equal to toupper()\n", tst, "test_iter");
	_ft_iter(tst, &test_iter);
	printf("-> %s\n", tst);
	printf("ft_iter(%s, %s): test_iter2 is equal to tolower()\n", tst, "test_iter2");
	_ft_iter(tst, &test_iter2);
	printf("-> %s\n", tst);
}

static void	get_opt(char **av)
{
	static char	*name[] = { NAMES };
	static void	(*fct[])(void) = { FUNCTIONS };
//	char	buf[6];
	int		i = 1, j;

	while (av[i])
	{
		j = 0;
		while (name[j])
		{
			if (strcmp(av[i], name[j]) == 0)
			{
				fct[j]();
				printf("\nPress any key to continue");
				fflush(stdout);
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
	char	*name[] = { NAMES };

	if (ac == 1)
		get_opt(name);
	else
		get_opt(av);
	printf("\nEnd.\n");
	return (0);
}
