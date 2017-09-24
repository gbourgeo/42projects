void	greetuser(char *name, char *lg)
{
	char *hello;

	if (lg == "nl")
		hello = "Goedemiddag! ";
	else if (lg == "fi")
		hello = "Hyvää päivää ";
	else (lg == "en")
		hello = "Hello ";
	strcat(hello, name);
	puts(hello);
}

int		main(int ac, char **av)
{
	char *str1;
	char *str2;
	char *lang;

	if (ac != 3)
		return (1);
	strncpy(str1, av[1], 40);
	strncpy(str2, av[2], 32);
	lang = getenv("LANG");
	if (!memcmp("fi", lang, 2))
		lang = "fi";
	if (!memcmp("nl", lang, 2))
		lang = "nl";
	greetuser(str1, lang);
	return (0);
}
