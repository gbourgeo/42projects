#include <stdio.h>
/*
	This program prints its own code source.
*/
static void print(char *str)
{
	printf(str,10,9,34,str);
}
int main(void)
{
	/*
	  This is what we call a quine.
	*/
	char *str = "#include <stdio.h>%1$c/*%1$c%2$cThis program prints its own code source.%1$c*/%1$cstatic void print(char *str)%1$c{%1$c%2$cprintf(str,10,9,34,str);%1$c}%1$cint main(void)%1$c{%1$c%2$c/*%1$c%2$c  This is what we call a quine.%1$c%2$c*/%1$c%2$cchar *str = %3$c%s%3$c;%1$c%2$cprint(str);%1$c%2$creturn (0);%1$c}%1$c";
	print(str);
	return (0);
}
