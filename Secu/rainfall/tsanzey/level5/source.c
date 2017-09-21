void	o(void)
{
	system("/bin/sh");
	exit(1);
}

void	n(void)
{
	char buff[520];
	
	fgets(buff, sizeof(buff), stdin);

	printf(buff);
	exit(1);
}

int		main(void)
{
	n();
}
