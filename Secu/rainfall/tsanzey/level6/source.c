int		n(void)
{
	system("/bin/cat /home/user/level7/.pass");
	return (0);
}

int		m(void)
{
	puts("Nope");
	return (0);
}

int		main(void)
{
	void *ptr1;
	int *ptr2;

	ptr1 = malloc(64);
	ptr2 = malloc(4);

	ptr2 = m();
	strcpy(ptr1, argv[1]);
	ptr2();
	return (0);
}
