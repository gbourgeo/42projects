#include <stdio.h>

int
main(int ac, char **av) {
	if (ac == 1)
		return (0x0);
	while (ac-- > 1)
		printf("%s\n", av[ac]);
	return (0x0);
}
