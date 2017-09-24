int	main(int ac, char **av)
{
	FILE* file;

	file = fopen("/home/user/end/.pass", "r");
	if (file == NULL)
		return (-1);
	return (0);
}
