
#include <stdio.h>
#include <sys/resource.h>

int main()
{
	printf("%ld, %ld\n", sizeof(struct rlimit), sizeof(short));
}
