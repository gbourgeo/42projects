int		v(void)
{
	int		pass = 0;
	char	buff[520];

	fgets(buff);
	printf(buff);

	if (pass == 64)
	{
		fwrite("Wait what ???");
		system("/bin/sh");
	}
	return (0);
}

int		main(void)
{
	v();
}
