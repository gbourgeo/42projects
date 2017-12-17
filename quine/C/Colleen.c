#include <stdio.h>
/*
	This program prints its own code source.
*/
int main(void)
{
	/*
	  This is what we call a quine.
	*/
	char *str = "#include <stdio.h>%c/*%c%cThis program prints its own code source.%c*/%cint main(void)%c{%c%c/*%c%c  This is what we call a quine.%c%c*/%c%cchar *str = %c%s%c;%c%cprintf(str, 10, 10,9, 10, 10, 10, 10,9, 10,9, 10,9, 10,9, 34,str,34, 10,9, 10,9, 10, 10);%c%creturn (0);%c}%c";
	printf(str, 10, 10,9, 10, 10, 10, 10,9, 10,9, 10,9, 10,9, 34,str,34, 10,9, 10,9, 10, 10);
	return (0);
}
