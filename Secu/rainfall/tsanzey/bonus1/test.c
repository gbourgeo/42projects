/* width1.c - exploiting a trivial widthness bug */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	//int i;
	int ui;

//	i = atoi(argv[1]);
	ui = atoi(argv[1]);


//	printf("i = %d\t\t0x%x\n", i, i);
	printf("ui = %d | i = %d\t\t0x%x\n", ui, ui*sizeof(int), ui);
	return 0;
}

