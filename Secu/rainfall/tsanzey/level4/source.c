int	p(char *str)
{
	printf(str);
}

int	n(void)
{
	char 	buff[512];
	int 	ret = 0;
	fgets(buff, 512, stdin);
	p(buff);

	if (ret == 0x1025544)
	{
		system("/bin/cat /home/user/level5/.pass");
	}
}

int	main(void)
{
	n();
}
