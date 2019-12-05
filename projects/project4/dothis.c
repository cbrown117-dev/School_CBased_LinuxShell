#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
	int i, x= 0;
	x = atoi(argv[1]);

	for(i=0;i<x;i++){
		printf("in for loop\n");
	}

return 0;
}
