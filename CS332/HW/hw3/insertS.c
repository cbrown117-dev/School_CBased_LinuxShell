#include <stdio.h>
#include <stdlib.h>

void insertS(int* A, int n){
	int i,j,len;
	len = n;
	
	for(j=1;j<len;j++){
		int key = *(A + j);
		i = j-1;
		while(i >= 0 && *(A+i) > key){
			*(A + i + 1) = *(A+i);
			i--;
		}
		*(A+i+1) = key;
	}

	for(i=0;i<len;i++){  
		printf("%d ", *(A+i));
	}
}

int main(int argc, char *argv[]){

	FILE *fp = fopen(argv[1], "r");

	int arr[20];
	int i;

	printf("not sorted array\n");

	while(!feof(fp)){
		fscanf(fp, "%d", &(*(arr + i)));
		i++;
	}

	for(i=0;i<20;i++){
		printf("%d ", *(arr+i));
	}
	printf("sorted array \n");	
	insertS(arr,20);

return 0;
}
