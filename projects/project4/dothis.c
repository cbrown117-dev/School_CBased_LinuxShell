#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
	int i, x= 0;
	x = atoi(argv[1]);

	printf("x is %d\n", x);
	for(i=0;i<x;i++){
		printf("in loop\n");
	}

return 0;
}
