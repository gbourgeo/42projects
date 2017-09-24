#define SIZE 4096

void	p(char *dst)
{
	char	buff[SIZE];

	puts(" - ");
	read(0, buff, SIZE);
	strchr(buff, '\n');
	strncpy(dst, buff, 20);
}


char	*pp(char *str)
{
	char *str1, *str2;

	p(str1);
	p(str2);

	strcpy(str, str1);
	strcat(str, str2);
}

int		main(void)
{
	char *str;

	pp(str);
	puts(str);
	return;
}
