
#include <stdio.h>
#include <sys/resource.h>
#include "ft_malloc.h"

int main()
{
	printf("%ld, %ld\n", sizeof(struct rlimit), sizeof(short));
	printf("%ld, %ld\n", sizeof(t_head *), sizeof(t_head));
	printf("%ld, %ld\n", sizeof(int), sizeof(size_t));
}
