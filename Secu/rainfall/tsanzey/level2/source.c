char	*p()
{
	char buf[64];
	int ret;
	
	fflush(stdout);
	gets(buf);
	
	if ((ret & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", ret);
		exit(0);
	}
	puts(buf);
	return strdup(buf);
}

int	main(void)
{
	p();
}
