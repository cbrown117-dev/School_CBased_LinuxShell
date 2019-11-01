#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv){

	int a = atoi(argv[1]);

	printf("a = %d\n", a);

	//do math function
	int b = a + 5;
	printf("b = %d\n", b);
	
return 0;
}
