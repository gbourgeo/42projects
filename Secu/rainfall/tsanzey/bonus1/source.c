int		main(int ac, char **argv)
{
	char buff[40];
	unsigned int i = atoi(argv[1]);

	if (i >= 10)
		return (1);
	memcpy(buff, argv[2], i * sizeof(int));
	if (i == 0x574f4c46) // "FLOW"
		execl("/bin/sh", "sh");
	return (0);
}
