#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main (int argc, char **argv){
	int x  = atoi(argv[1]);
	
	sleep(x);

	printf("we waited for %d seconds\n", x);
	return 0;
}
