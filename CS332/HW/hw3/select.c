#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void findMin(double *arr){

	double min = arr[0];
	int i = 0;
	for (i = 0; i<200;i++){
		if(arr[i] < min) 
			min = arr[i];
	}

	printf("min num is %lf", min);
}

int main(){
	double drand48(void);
	double arr[200];

	srand48((unsigned int)time(NULL));	
	int i = 0;
	for(i = 0; i<200;i++){
		arr[i] = drand48();
	}

	findMin(arr);

return 0;
}
