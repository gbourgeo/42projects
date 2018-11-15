int		shift_handler(int value, int state, int *modifier)
{
	if (state == 2)
		return 1;
	if (state == 0)
		*modifier -= (1 << value);
	else if (state == 1)
		*modifier += (1 << value);
	return 1;
}

int		lock_handler(int value, int state, int *modifier, int *locker)
{
	if (state != 1)
		return 1;
	locker[value] = !(locker[value]);
	if (locker[value] == 0)
		*modifier -= (1 << value);
	else
		*modifier += (1 << value);
	return 1;
}