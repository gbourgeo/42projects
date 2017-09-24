#include <stdio.h>

int	main(int ac, char **av)
{
	int i = 0;

	int fd = open(av[1]);
	char buf[1024];
	int ret;

	ret = read(fd, buf, 1024);
	buf[ret] = '\0';
	while (buf[i])
	{
		printf("%c", buf[i] - i);
		i++;
	}
	printf("\n");
	return (0);
}
