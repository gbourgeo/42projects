char	*c;

int		m()
{
	time_t time = time();	
	printf("%s - %d\n", c, time);
}

int		main(int argc, char **arg)
{
	void 	*ptr1;
	void 	*ptr2;

	ptr1 = malloc(8);
	ptr1 = 1;
	ptr1 + 4 = malloc(8);
	ptr2 = malloc(8);
	ptr2 = 2;
	ptr2 + 4 = malloc(8);

	strcpy(ptr1, argv[1]);
	strcpy(ptr2, argv[2]);

	FILE *tmp = fopen("/home/user/level8/.pass", "r");
	fgets(c, 68, tmp);
	puts("~~");
	return(0);
}
